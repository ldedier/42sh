/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 02:35:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 23:50:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_cdpath_check_perm:
**	Check if file designated by path exists, is a directory, and user have
**	right permissions to open it.
**
**	Returned Values :
**		SUCCESS : Everything is allright
**		ERROR : On of the condition is invalid.
*/

static int	sh_builtin_cd_cdpath_check_perm(
	char *path, char **curpath, t_args *args)
{
	struct stat	st;

	if ((stat(path, &st) == -1))
		return (ERROR);
	if (!S_ISDIR(st.st_mode))
		return (ERROR);
	if (access(path, X_OK))
		return (ERROR);
	*curpath = path;
	args[CD_HYPHEN_OPT].value = &args;
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : rule 5 : Filled *curpath using CDPATH\n"EOC);
	return (SUCCESS);
}

/*
**	5. Starting with the first pathname in the <colon>-separated pathnames of
**	CDPATH (see the ENVIRONMENT VARIABLES section) if  the  pathname
**	is non-null, test if the concatenation of that pathname, a <slash> character
**	if that pathname did not end with a <slash> character, and the directory
**	operand names a directory. If the pathname is null, test if the
**	concatenation of dot, a <slash> character, and the  operand	names
**	a directory. In either case, if the resulting string names an existing
**	directory, set curpath to that string and proceed to step 7. Otherwise,
**	repeat this step with the next pathname in CDPATH until all pathnames
**	have been tested.
**	In case of empty field, I changed behaviour by skipping this path,
**	to feat diff tests using bash as reference.
*/

static int	sh_builtin_cd_cdpath(
	t_context *context, char **curpath, char *param, t_args *args)
{
	char	*cdpath;
	char	*dir;
	char	*path;

	cdpath = sh_vars_get_value(context->env, context->vars, "CDPATH");
	path = NULL;
	while ((dir = ft_strsep(&cdpath, ":")))
	{
		if (path)
			ft_strdel(&path);
		if (*dir)
			path = ft_strjoin_path(dir, param);
		else
			continue ;
		if (!path)
			return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
		if (sh_builtin_cd_cdpath_check_perm(path, curpath, args) == SUCCESS)
			break ;
	}
	if (!dir && path)
		ft_strdel(&path);
	ft_strsep(NULL, NULL);
	return (SUCCESS);
}

/*
** sh_builtin_cd_rule5:
**	5. Starting with the first pathname in the <colon>-separated pathnames of
**	CDPATH (see the ENVIRONMENT VARIABLES section) if  the  pathname
**	is non-null, test if the concatenation of that pathname, a <slash> character
**	if that pathname did not end with a <slash> character, and the directory
**	operand names a directory. If the pathname is null, test if the
**	concatenation of dot, a <slash> character, and the  operand	names
**	a directory. In either case, if the resulting string names an existing
**	directory, set curpath to that string and proceed to step 7. Otherwise,
**	repeat this step with the next pathname in CDPATH until all pathnames
**	have been tested.
**	6. Set curpath to the directory operand. (correspond to second condition)
**
**	Returned Values
**		SUCCESS : Applied rule 5 and 6 successfully
**		FAILURE : Malloc error
*/

int			sh_builtin_cd_rule5(
	t_context *context, char **curpath, char *param, t_args *args)
{
	char	*cdpath;
	int		ret;

	cdpath = sh_vars_get_value(context->env, context->vars, "CDPATH");
	ret = SUCCESS;
	if (cdpath && *cdpath && !args[CD_HYPHEN_OPT].value)
		ret = sh_builtin_cd_cdpath(context, curpath, param, args);
	if (!ret && !*curpath)
	{
		if (!(*curpath = ft_strdup(param)))
			sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_rule5");
	}
	return (ret);
}
