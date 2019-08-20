/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_verbose.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:19:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/20 18:57:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_verbose_usage(t_context *context)
{
	ft_dprintf(context->fd[FD_ERR], SH_ERR_COLOR"verbose: usage: verbose on/");
	ft_dprintf(context->fd[FD_ERR], "off [lexer,ast,pipe,exec,expansion,");
	ft_dprintf(context->fd[FD_ERR], "traverse]\n"EOC);
	return (ERROR);
}

static int	sh_builtin_verbose_process_all(
	t_context *context, char key[8][20], char value[3])
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (!ret && key[i][0])
	{
		ret = sh_vars_assign_key_val(
			context->saved_env, context->vars, key[i], value);
		i++;
	}
	return (ret);
}

static int	sh_builtin_verbose_process(
	t_context *context, char key[8][20], char value[3])
{
	int			i;
	int			j;
	int			ret;

	i = 2;
	ret = 0;
	while (!ret && context->params->tbl[i])
	{
		j = 0;
		while (*key[j] && !ft_strequ(context->params->tbl[i], key[j] + 8))
			j++;
		if (*key[j])
			ret = sh_vars_assign_key_val(context->saved_env,
				context->vars, key[j], value);
		else if (!*key[j])
		{
			ret = sh_perror2_err_fd(context->fd[FD_ERR], SH_ERR2_INVALID_OPT,
				"verbose", context->params->tbl[i]);
			sh_builtin_verbose_usage(context);
		}
		i++;
	}
	if (i == 2)
		return (sh_builtin_verbose_process_all(context, key, value));
	return (ret);
}

int			sh_builtin_verbose(t_context *context)
{
	char		value[3];
	static char	key[9][20] = {"verbose_ast", "verbose_lexer", "verbose_exec",
				"verbose_pipe", "verbose_expansion", "verbose_builtin",
				"verbose_traverse", ""};
	int			ret;

	if (ft_strequ(context->params->tbl[1], "on"))
		ft_strcpy(value, "on");
	else if (ft_strequ(context->params->tbl[1], "off"))
		ft_strcpy(value, "");
	else
		return (sh_builtin_verbose_usage(context));
	ret = sh_builtin_verbose_process(context, key, value);
	if (ret)
		return (ret);
	return (ret);
}
