/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence_execute.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/14 21:26:27 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

int				sh_traverse_pipe_sequence_execute(t_ast_node *node,
		t_context *context)
{
	int ret;

	node->metadata.pipe_metadata.contexts = NULL;
	if (ft_lstlen(node->children) == 1)
	{
		context->current_pipe_sequence_node = NULL;
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		context->current_pipe_sequence_node = node;
		context->current_pipe_sequence_node
		->metadata.pipe_metadata.last_ret_value = 0;
		if ((ret = sh_traverse_tools_browse(node, context)) != SUCCESS)
			return (ret);
		return (sh_execute_pipe_sequence(context,
			node->metadata.pipe_metadata.contexts));
	}
}
