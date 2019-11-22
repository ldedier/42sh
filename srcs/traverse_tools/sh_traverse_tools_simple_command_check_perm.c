/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_simple_command_check_perm        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:23:20 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 13:13:49 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** check_for_symlink_loop:
**	Checking for symlink loop, and for too long cycles (up to 10).
**	Just call it with st filled by lstat on your symlink, path as
**	you symlink path, and i = 0 (stack counter).
**
**	Returned Values
**		SUCCESS : Found too many symlinks
**		ERROR : Cycle stopped to early
*/

int			check_for_symlink_loop(struct stat *st, char *path, int i)
{
	char		buffer[200];
	struct stat	current;
	ssize_t		index;

	if (i > 10)
		return (SUCCESS);
	if ((index = readlink(path, buffer, 200)) == -1)
		return (ERROR);
	buffer[index] = '\0';
	if (lstat(buffer, &current) == -1)
		return (ERROR);
	if (current.st_ino == st->st_ino && current.st_dev == st->st_dev)
		return (SUCCESS);
	return (check_for_symlink_loop(st, buffer, i + 1));
}

/*
** sh_traverse_sc_check_perm_quiet:
**	(Do the same than sh_traverse_sc_check_perm, with no error messages shown)
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return ERROR.
**	shell->ret_value is not modified.
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

long		sh_traverse_sc_check_perm_quiet(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (ERROR);
	if (stat(path, &st) == -1)
		return (ERROR);
	if (access(path, X_OK))
		return (ERROR);
	if (S_ISDIR(st.st_mode))
		return (ERROR);
	if (!S_ISREG(st.st_mode))
		return (ERROR);
	return (SUCCESS);
}

static long	sh_traverse_sc_check_perm_reg(t_context *context, struct stat st,
			char *command_name)
{
	if (S_ISDIR(st.st_mode))
	{
		sh_env_update_ret_value(context->shell, SH_RET_NOT_EXECUTABLE);
		return (sh_perror(context->params->tbl[0], SH_ERR1_IS_DIR));
	}
	if (sh_verbose_exec())
		ft_dprintf(2, "%s is not a regular file\n", command_name);
	sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
	return (sh_perror_err(SH_ERR1_CMD_NOT_FOUND, command_name));
}

/*
** sh_traverse_sc_check_perm:
**	Check if a file pointed by path exists, is a regular file,
**	can be executed by current user. If not it return an error
**	and print error message on stderr.
**	shell->ret_value is updated if any error occured
**
**	return Value:
**		SUCESS : file can be considered as an executable
**		ERROR : file cannot be considered as an executable
*/

long		sh_traverse_sc_check_perm(t_context *context, char *path,
			char *command_name)
{
	struct stat		st;

	if (stat(path, &st) == -1 && lstat(path, &st) != -1)
	{
		if (check_for_symlink_loop(&st, path, 0) == SUCCESS)
		{
			sh_env_update_ret_value(context->shell, SH_RET_NOT_EXECUTABLE);
			return (sh_perror_err(command_name, SH_ERR2_TOO_MANY_SYMLINK));
		}
		else
			return (sh_perror_err(command_name, SH_ERR2_NO_SUCH_FILE_OR_DIR));
	}
	if (stat(path, &st) == -1)
	{
		sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
		return (sh_perror_err(command_name, SH_ERR2_NO_SUCH_FILE_OR_DIR));
	}
	if (access(path, X_OK))
	{
		sh_env_update_ret_value(context->shell, SH_RET_NOT_EXECUTABLE);
		return (sh_perror_err(command_name, SH_ERR1_PERM_DENIED));
	}
	if (!S_ISREG(st.st_mode))
		return (sh_traverse_sc_check_perm_reg(context, st, command_name));
	return (SUCCESS);
}
