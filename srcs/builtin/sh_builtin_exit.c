/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:14:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 04:41:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_builtin_exit_is_numeric_value(char *str)
{
	int		len;
	int		offset;

	offset = 0;
	if (str[0] == '-' || str[0] == '+')
		offset++;
	if (!ft_isdigit_only(str + offset))
		return (0);
	len = ft_strlen(str + offset);
	if (len < 10)
		return (1);
	else if (len == 10 && str[0] == '-' && ft_strcmp("-2147483648", str) >= 0)
		return (1);
	else if (len == 10 && ft_strcmp("2147483647", str + offset) >= 0)
		return (1);
	return (0);
}

static int		sh_builtin_exit_treat_first_arg(t_context *context, int *ret)
{
	if (!sh_builtin_exit_is_numeric_value(context->params->tbl[1]))
	{
		sh_perror2(context->params->tbl[1],
		"exit", "numeric argument required");
		sh_env_update_ret_value(context->shell, 2);
		context->shell->running = 0;
		return (ERROR);
	}
	else
		*ret = ft_atoi(context->params->tbl[1]) & 0xff;
	return (SUCCESS);
}

int				sh_builtin_exit(t_context *context)
{
	int		ret;

	ret = -1;
	if (context->params->tbl[1])
		if (sh_builtin_exit_treat_first_arg(context, &ret) == ERROR)
			return (ERROR);
	if (context->params->tbl[1] && context->params->tbl[2])
	{
		sh_perror_err(context->params->tbl[0], SH_ERR1_TOO_MANY_ARGS);
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
		return (STOP_CMD_LINE);
	}
	if (ret == -1)
		ret = context->shell->ret_value;
	if (sh_verbose_builtin())
		ft_dprintf(2,
		MAGENTA"exit: exit value set to : %d\n"EOC, ret);
	sh_env_update_ret_value(context->shell, ret);
	context->shell->running = 0;
	return (SUCCESS);
}
