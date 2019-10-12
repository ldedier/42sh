/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_get_exec_node.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:00:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/11 22:02:53 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** get_node_to_exec :
** This function look over the t_list of LIST (grammar) content or
** the t_list of TERM (grammar) content, followed the symbol argument.
** symbol = SEPARATOR_OP if we are in list
** symbol = SEPARATOR if we are in compound_command
**
** If we find a sequence follow by a separator, we execute
** sh_get_separator_op or sh_get_separator
** which dispatches the execution of the and_or node between
** the different separators found.
**
** If they are no separator, we just call the next level on the ast.
*/

int 	get_node_to_exec(t_ast_node *node, t_context *context,
		t_symbol_id symbol, int (*f)(t_ast_node *, t_ast_node *, t_context *))
{
	t_list 		*lst;
	t_ast_node	*curr_node;
	t_ast_node	*node_to_exec;
	int 		ret;

	lst = node->children;
	node_to_exec = NULL;
	ret = SUCCESS;
	while (lst && ret == SUCCESS)
	{
		curr_node = lst->content;
		if (curr_node->symbol->id == sh_index(symbol))
		{
			// For each seperator op, we need a new job.
			g_job_ctrl->job_added = 0;
			context->cmd_type = SIMPLE_NODE;
			ret = f(node_to_exec, curr_node->children->content, context);
			node_to_exec = NULL;
		}
		else
			node_to_exec = curr_node;
		lst = lst->next;
	}
	// For the last command.
	context->cmd_type = SIMPLE_NODE;
	g_job_ctrl->job_added = 0;
	if (g_job_ctrl->ampersand_eol != 0)
		context->cmd_type |= BG_NODE;
	if (node_to_exec && ret == SUCCESS)
	{
		if (g_job_ctrl->ampersand_eol != 0)
			context->wait_flags |= WNOHANG;
		if (g_job_ctrl->interactive && g_job_ctrl->ampersand_eol)
		{
			if ((ret = job_add(0)) != SUCCESS)
					return (ret);
			g_job_ctrl->job_added = 1;
		}
		ret = sh_traverse_and_or(node_to_exec, context);
	}
	return (ret);
}

