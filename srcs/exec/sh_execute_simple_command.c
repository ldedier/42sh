/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_simple_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/25 10:26:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int	sh_no_slash_cmd(t_context *context)
{
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	sh_slash_cmd(t_context *context)
{
	if (!(context->path = ft_strdup(context->params->tbl[0])))
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	return (SUCCESS);
}

int			sh_execute_simple_command(
		t_ast_node *father_node, t_context *context)
{
	int	ret;

	if (context->params->tbl && context->params->tbl[0]
			&& (context->builtin = sh_builtin_find(context)))
		ret = sh_execute_builtin(father_node, context);
	else
	{
		if (context->params->tbl && context->params->tbl[0])
		{
			if (!ft_strchr(context->params->tbl[0], '/'))
			{
				ret = sh_no_slash_cmd(context);
				if (ret != SUCCESS)
					return (ret);
			}
			else if (sh_slash_cmd(context) == FAILURE)
				return (FAILURE);
		}
		ret = sh_execute_binary(father_node, context);
	}
	return (ret);
}
