/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_get_exec_node.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:00:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/26 08:07:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	process_node_to_exec(
		t_ast_node *node_to_exec, t_context *context, int ret)
{
	g_job_ctrl->job_added = 0;
	context->wflags = 0;
	context->cmd_type = SIMPLE_NODE;
	if (node_to_exec && ret == SUCCESS)
	{
		g_job_ctrl->ampersand = g_job_ctrl->ampersand_eol;
		ret = sh_traverse_and_or(node_to_exec, context);
	}
	return (ret);
}

static void	get_node_to_exec_init(
	t_list **lst, t_ast_node **node_to_exec, int *ret, t_ast_node *node)
{
	*lst = node->children;
	*node_to_exec = NULL;
	*ret = SUCCESS;
}

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

int			get_node_to_exec(t_ast_node *node, t_context *context,
		t_symbol_id symbol, int (*f)(t_ast_node *, t_ast_node *, t_context *))
{
	t_list		*lst;
	t_ast_node	*curr_node;
	t_ast_node	*node_to_exec;
	int			ret;

	get_node_to_exec_init(&lst, &node_to_exec, &ret, node);
	while (lst && ret == SUCCESS)
	{
		curr_node = lst->content;
		if (curr_node->symbol->id == sh_index(symbol))
		{
			g_job_ctrl->job_added = 0;
			g_job_ctrl->ampersand = 0;
			context->cmd_type = SIMPLE_NODE;
			context->wflags = 0;
			ret = f(node_to_exec, curr_node->children->content, context);
			if (context->shell->ret_value == 130)
				return (SUCCESS);
			node_to_exec = NULL;
		}
		else
			node_to_exec = curr_node;
		lst = lst->next;
	}
	return (process_node_to_exec(node_to_exec, context, ret));
}
