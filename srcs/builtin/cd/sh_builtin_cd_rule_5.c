/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 02:35:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/11 05:12:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_cd_cdpath(
	t_context *context, char **curpath, char *param, t_args *args)
{
	char		*cdpath;
	char		**split;
	int			i;
	char		*path;
	struct stat	st;

	if (!(cdpath = sh_vars_get_value(context->env, context->vars, "CDPATH")))
		return (SUCCESS);
	if (!(split = ft_strsplit(cdpath, ':')))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
	i = 0;
	path = NULL;
	while (split[i])
	{
		i++;
		if (path)
			ft_strdel(&path);
		if (!split[i - 1] && !*split[i - 1])
			continue ;
		if (!(path = ft_strjoin_path(split[i - 1], param)))
		{
			ft_strtab_free(split);
			return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
		}
		if ((stat(path, &st)))
			continue ;
		if (!S_ISDIR(st.st_mode))
			continue ;
		if (access(path, X_OK))
			continue ;
		*curpath = path;
		args[CD_HYPHEN_OPT].value = &args;
		ft_strtab_free(split);
		return (SUCCESS);
	}
	ft_strtab_free(split);
	if (path)
		ft_strdel(&path);
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
	if (cdpath && *cdpath)
		ret = sh_builtin_cd_cdpath(context, curpath, param, args);
	if (!ret && !*curpath)
	{
		if (!(*curpath = ft_strdup(param)))
			sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_rule5");
	}
	return (ret);
}
