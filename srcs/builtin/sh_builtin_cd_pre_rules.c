/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_pre_rules.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:50:45 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/30 15:04:31 by jmartel          ###   ########.fr       */
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
	int *index, char **curpath, char **argv)
{
	int		ret;

	*curpath = NULL;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, index))
		return (sh_builtin_usage(args, argv[0], CD_USAGE, context));
	if (argv[*index] && argv[*index + 1])
		return (sh_perror_err_fd(context->fd[FD_ERR], argv[0], SH_ERR1_TOO_MANY_ARGS));
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
	t_context *context, char *param, char **curpath)
{
	char	*home;
	int		ret;

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
	else if ((ret = sh_builtin_cd_rule5(context, curpath, param)) != SUCCESS)
		return (ret);
	if (!*curpath)
	{
		sh_perror_fd(
			context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_builtin_cd_pre_rules");
		return (FAILURE);
	}
	return (SUCCESS);
}

int			sh_builtin_cd_rule5(t_context *context, char **curpath, char *param)
{
	char	*cdpath;

	cdpath = sh_vars_get_value(context->env, NULL, "CDPATH");
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
	sh_perror_fd(context->fd[FD_ERR], "CD_PATH", "not implemented yet");
	return (ERROR);
}
