/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_10.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 07:20:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 14:43:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_update_pwd:
**	Update the PWD and OLDPW env variables. New value depend of options given.
**	If -P had been used, the getcwd (3) function will be used.
**	Else, the current curpath var will be used.
**	In physical mode pwd s freed because it was malloced by getcwd (3).
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS : updated the two env vars
*/

static int	sh_builtin_cd_update_pwd(
	t_context *context, t_args *args, char *curpath)
{
	char		*pwd;
	char		*old_pwd;
	int			ret;

	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
		pwd = curpath;
	else
		pwd = sh_builtin_pwd_physical();
	if (!pwd)
		return (ERROR);
	ret = SUCCESS;
	if ((old_pwd = sh_vars_get_value(context->env, NULL, "PWD")))
		ret = sh_vars_assign_key_val(
			context->saved_env, NULL, "OLDPWD", old_pwd);
	if (!ret)
		ret = sh_vars_assign_key_val(context->saved_env, NULL, "PWD", pwd);
	if (args[CD_P_OPT].priority > args[CD_L_OPT].priority)
		free(pwd);
	return (ret);
}

/*
** sh_builtin_cd_check_perms:
**	Check if file designated by path exists, user have sufficient permissions.
**	Error messages are written on fderr if needed.
**
**	Returned Values:
**		SUCCESS : file is invalid
**		ERROR : file is invalid
*/

int			sh_builtin_cd_check_perms(char *curpath, char *param)
{
	int			ret;
	struct stat	st;

	ret = SUCCESS;
	if (stat(curpath, &st) == -1 && lstat(curpath, &st) != -1)
	{
		if (check_for_symlink_loop(&st, curpath, 0) == SUCCESS)
			ret = sh_perror2_err(
				"too many levels of symbolic links", "cd", param);
		else
			ret = sh_perror2_err(param, "cd", SH_ERR2_NO_SUCH_FILE_OR_DIR);
	}
	else if (stat(curpath, &st) == -1)
		ret = sh_perror2_err(param, "cd", SH_ERR2_NO_SUCH_FILE_OR_DIR);
	else if (!S_ISDIR(st.st_mode))
		ret = sh_perror2_err(SH_ERR1_NOT_A_DIR, "cd", param);
	else if (access(curpath, X_OK))
		ret = sh_perror2_err(SH_ERR1_PERM_DENIED, "cd", param);
	return (ret);
}

/*
** sh_builtin_cd_rule10:
**	10. The cd utility shall then perform actions equivalent to the chdir()
**	function called with curpath as the path argument. If these actions
**	fail for any reason, the cd utility shall display an appropriate error
**	message and the remainder of this step shall not be executed. If
**	the	-P  option  is	not  in  effect, the PWD environment variable
**	shall be set to the value that curpath had on entry to step 9
**	(i.e., before conversion to a relative pathname). If the -P option is in
**	effect, the PWD environment variable shall be set to the string  that
**	would  be output by pwd -P.	If there is insufficient permission on
**	the new directory, or on any parent of that directory, to determine
**	the current working directory, the value of the PWD environment
**	variable is unspecified.
**	If hyphen option was filled, it print current working directory. This
**	correspond to 'cd -' case, or if CDPATH search was successfull.
**
**	Returned Values:
**		FAILURE : malloc error
**		ERROR : write error
**		SUCCESS : Successfully changed current directory,
**					and updated PWD and OLDPWD
*/

int			sh_builtin_cd_rule10(
	t_context *context, char *curpath, t_args *args, char *param)
{
	int		ret;

	ret = SUCCESS;
	if (curpath && *curpath)
	{
		ret = sh_builtin_cd_check_perms(curpath, param);
		if (!ret)
			if (chdir(curpath) == -1)
				ret = sh_perror2(param, "cd", "unable to process");
		if (!ret)
			sh_builtin_cd_update_pwd(context, args, curpath);
		if (!ret && args[CD_HYPHEN_OPT].value)
		{
			if (write(FD_OUT, NULL, 0))
			{
				return (sh_perror2_err("write error",
					context->params->tbl[0], SH_ERR1_BAD_FD));
			}
			else
				ft_dprintf(FD_OUT,
					"%s\n", sh_vars_get_value(context->saved_env, NULL, "PWD"));
		}
	}
	return (ret);
}
