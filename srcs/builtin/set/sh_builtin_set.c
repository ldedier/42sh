/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 16:02:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_set_param(t_context *context, int *index)
{
	if (!ft_strcmp(context->params->tbl[*index], "-o"))
	{
		(*index)++;
		if (*index == (int)context->params->current_size)
			return (print_options_minus(context->shell));
		else
			return (add_option(context, *index));
	}
	else if (!ft_strcmp(context->params->tbl[*index], "+o"))
	{
		(*index)++;
		if (*index == (int)context->params->current_size)
			return (print_options_plus(context->shell));
		else
			return (remove_option(context, *index));
	}
	else
	{
		print_builtin_usage();
		return (ERROR);
	}
}

int			sh_builtin_set_args(t_context *context)
{
	int i;
	int ret;

	i = 1;
	while (i < (int)context->params->current_size)
	{
		if ((ret = sh_builtin_set_param(context, &i)))
			return (ret);
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_set(t_context *context)
{
	if (context->params->current_size == 1)
		return (sh_builtin_set_print(context));
	else
		return (sh_builtin_set_args(context));
	return (SUCCESS);
}
