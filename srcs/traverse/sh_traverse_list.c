/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 18:35:02 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

static int	sh_traverse_list_redir_exec(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ret = SUCCESS;

	ptr = node->children;
	while (ptr != NULL && context->shell->running)
	{
		job_add();
		child = (t_ast_node *)ptr->content;
		if ((ptr = (ptr)->next))
			ptr = (ptr)->next;
		context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
		ret = g_grammar[child->symbol->id].traverse(child, context);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
		// job_print();
		// job_exec();
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == STOP_CMD_LINE)
			return (ERROR);
	}
	return (ret);
}

int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int		ret;

	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		sh_traverse_tools_show_traverse_start(node, context);
		return (sh_traverse_tools_browse(node, context));
	}
	else
	{
		sh_traverse_tools_show_traverse_start(node, context);
		ret = sh_traverse_list_redir_exec(node, context);
		return (ret);
	}
}
