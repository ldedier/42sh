/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/22 18:41:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_set(t_context *context)
{
	int		i;

	i = 0;
	while (context->env->tbl[i])
	{
		ft_putstr_fd(context->env->tbl[i], FD_OUT);
		ft_putchar_fd('\n', FD_OUT);
		i++;
	}
	i = 0;
	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err_fd(FD_ERR, "write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	while (context->vars->tbl[i])
	{
		if (!(*(char*)(context->vars->tbl[i]) == '?'
			|| *(char*)(context->vars->tbl[i]) == '$'
			|| *(char*)(context->vars->tbl[i]) == '#'))
		{
			ft_putstr_fd(context->vars->tbl[i], FD_OUT);
			ft_putchar_fd('\n', FD_OUT);
		}
		i++;
	}
	return (SUCCESS);
}
