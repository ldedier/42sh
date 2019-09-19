/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_pre_rules.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:50:45 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/19 17:23:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_cd_parser_hyphen(
	t_context *context, t_args *args, char **curpath, int i)
{
	char	*oldpwd;

	if (!(oldpwd = sh_vars_get_value(context->env, NULL, "OLDPWD")))
	{
		sh_perror_err_fd(context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "OLDPWD");
		return (ERROR);
	}
	if (!(*curpath = ft_strdup(oldpwd)))
	{
		sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_parser_hyphen");
		return (FAILURE);
	}
	free(context->params->tbl[i]);
	if (!(context->params->tbl[i] = ft_strdup(*curpath)))
	{
		ft_strdel(curpath);
		return (sh_perror_fd(context->fd[FD_ERR],
			SH_ERR1_MALLOC, "sh_builtin_cd_parser_hyphen"));
	}
	args[CD_HYPHEN_OPT].value = args;
	return (SUCCESS);
}

int			sh_builtin_cd_parser(t_context *context, t_args *args,
	int *index, char **curpath)
{
	int		ret;
	char	**argv;

	argv = (char**)context->params->tbl;
	*curpath = NULL;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, index))
		return (sh_builtin_usage(args, argv[0], CD_USAGE, context));
	if (argv[*index] && argv[*index + 1])
	{
		return (sh_perror_err_fd(
			context->fd[FD_ERR], argv[0], SH_ERR1_TOO_MANY_ARGS));
	}
	if (ft_strequ(argv[*index], "-"))
		if ((ret = sh_builtin_cd_parser_hyphen(context, args, curpath, *index)))
			return (ret);
	if (!args[CD_P_OPT].value)
	{
		args[CD_L_OPT].value = &args;
		args[CD_L_OPT].priority++;
	}
	return (SUCCESS);
}

int			sh_builtin_cd_pre_rules(
	t_context *context, char *param, char **curpath, t_args *args)
{
	char	*home;

	home = sh_vars_get_value(context->env, NULL, "HOME");
	if (*curpath)
		;
	else if ((!param) && (!home || !*home))
		return (sh_perror_err_fd(
			context->fd[FD_ERR], SH_ERR1_ENV_NOT_SET, "HOME"));
	else if (!param)
		*curpath = ft_strdup(home);
	else if (*param == '/')
		*curpath = ft_strdup(param);
	else if (*param == '.' || ft_strnstr(param, "..", 2))
		*curpath = ft_strdup(param);
	else
		return (sh_builtin_cd_rule5(context, curpath, param, args));
	if (!*curpath)
	{
		sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_pre_rules");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	sh_builtin_cd_cdpath(
	t_context *context, char **curpath, char *param, t_args *args)
{
	char	*cdpath;
	char	**split;
	int		i;
	char	*path;
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
			return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
		if ((stat(path, &st)))
			continue ;
		if (!S_ISDIR(st.st_mode))
			continue ;
		if (access(*curpath, X_OK))
			continue ;
		*curpath = path;
		args[CD_HYPHEN_OPT].value = &args;
		return (SUCCESS);
	}
	if (path)
		ft_strdel(&path);
	if (!((*curpath) = ft_strdup(param)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_cdpath"));
	return (SUCCESS);
}

int			sh_builtin_cd_rule5(t_context *context, char **curpath, char *param, t_args *args)
{
	char	*cdpath;

	cdpath = sh_vars_get_value(context->env, context->vars, "CDPATH");
	if (!cdpath || !*cdpath)
	{
		*curpath = ft_strjoin_path(".", param);
		if (!curpath)
		{
			sh_perror_fd(
				context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_rule5");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (sh_builtin_cd_cdpath(context, curpath, param, args));
}
