/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_reset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:45:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/06/07 14:21:11 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
void	sh_traverse_tools_reset_context(t_context *context)
{
	sh_traverse_tools_reset_params(context);
}

void	sh_traverse_tools_reset_params(t_context *context)
{
	int		i;

	i = 0;
	while (i < (int)context->params->current_size)
	{
		free(context->params->tbl[i]);
		context->params->tbl[i] = NULL;
		i++;
	}
	context->params->current_size = 0;
	if (context->path)
		ft_strdel(&context->path);
	context->builtin = NULL;
}
*/
