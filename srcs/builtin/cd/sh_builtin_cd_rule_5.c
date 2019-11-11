/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 02:35:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/11 03:17:15 by jmartel          ###   ########.fr       */
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
	if (!((*curpath) = ft_strdup(param)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
	return (SUCCESS);
}

int			sh_builtin_cd_rule5(
	t_context *context, char **curpath, char *param, t_args *args)
{
	char	*cdpath;

	cdpath = sh_vars_get_value(context->env, context->vars, "CDPATH");
	if (!cdpath || !*cdpath)
	{
		*curpath = ft_strjoin_path(".", param);
		if (!curpath)
		{
			sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_rule5");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (sh_builtin_cd_cdpath(context, curpath, param, args));
}
