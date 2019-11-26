/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type_search_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 07:43:39 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** show_success_message:
**	Update found var, then show message depending on flags.
**
**	Returned Values
**		SUCCESS : Stop looking cause -a is not active.
**		ERROR : If in -a case, mean continue reading.
*/

static int	show_success_message(
	t_context *context, t_args *args, char *name, int *found)
{
	(*found) += 1;
	if (args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
		ft_dprintf(FD_OUT, "%s\n", context->path);
	else if (args[TYPE_T_OPT].value)
		ft_dprintf(FD_OUT, "file\n");
	else
		ft_dprintf(FD_OUT, "%s is %s\n", name, context->path);
	if (args[TYPE_A_OPT].value)
		return (ERROR);
	else
		return (SUCCESS);
}

/*
** search_in_dir_check_perm_quiet:
**	Same as sh_traverse_sc_check_perm_quiet function, but do not check
**	permissions, as bash does.
**
**	Returned Values
**		SUCCESS : Exists and type is good
**		ERROR : Something is is wrong, file is not valid.
*/

static int	search_in_dir_check_perm(char *path)
{
	struct stat	st;

	if (lstat(path, &st) == -1)
		return (ERROR);
	if (stat(path, &st) == -1)
		return (ERROR);
	if (S_ISDIR(st.st_mode))
		return (ERROR);
	if (!S_ISREG(st.st_mode))
		return (ERROR);
	return (SUCCESS);
}

/*
** search_in_dir_check_perm:
**	For a given binary, described by path and dirent->d_nae concatenation,
**	check that permissions and type are valid.
**	If yes it fill context->path variable with path obtained by concatenation.
**
**	Returned Values
**		SUCCESS : Permissions are good
**		KEEP_READ : Permissions are not good
**		FAILURE : malloc error
*/

static int	search_in_dir_do_file_match(char *path, DIR *dir,
			t_dirent *dirent, t_context *context)
{
	char *buf;

	if (!(buf = ft_strjoin_path(path, dirent->d_name)))
	{
		closedir(dir);
		return (sh_perror(SH_ERR1_MALLOC,
					"search_in_dir_check_perm"));
	}
	if (search_in_dir_check_perm(buf) == ERROR)
	{
		free(buf);
		return (KEEP_READ);
	}
	if (context->path)
		ft_strdel(&context->path);
	context->path = buf;
	closedir(dir);
	return (SUCCESS);
}

/*
** sh_builtin_type_search_in_dir:
**	For an open directory (dir), check if any file with right type,
**	can match name, in this directory.
**
**	Returned Values
**		SUCCESS : Found one match
**		ERROR : Do not found any match
**		FAILURE : malloc error
*/

static int	sh_builtin_type_search_in_dir(
	char *path, DIR *dir, t_context *context, char *name)
{
	t_dirent	*dirent;
	int			ret;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, name))
		{
			if ((ret = search_in_dir_do_file_match(path, dir,
				dirent, context)) != KEEP_READ)
				return (ret);
			else
				return (SUCCESS);
		}
	}
	closedir(dir);
	return (ERROR);
}

/*
** sh_builtin_type_search_in_path:
**	Look for any or all binaries matching name, depending on options (-a).
**	It parse and use PATH env variable as in binary research.
**
**	Returned Values
**		SUCCESS : Found at least on matching binary.
**		ERROR : Do not found any matches.
**		FAILURE : malloc error
*/

int			sh_builtin_type_search_in_path(
	t_context *context, char *name, t_args args[])
{
	char		*env_path;
	char		*path;
	DIR			*dir;
	int			found;
	int			ret;

	found = 0;
	if (!(env_path = sh_vars_get_value(context->env, context->vars, "PATH")))
		return (ERROR);
	while ((path = ft_strsep(&env_path, ":")))
	{
		if (!(dir = opendir(path)))
			continue ;
		ret = sh_builtin_type_search_in_dir(path, dir, context, name);
		if (ret == SUCCESS && context->path)
			ret = show_success_message(context, args, name, &found);
		if (ret != ERROR)
			break ;
	}
	ft_strsep(NULL, 0);
	if (ret == FAILURE)
		return (FAILURE);
	if (found)
		return (SUCCESS);
	return (ERROR);
}
