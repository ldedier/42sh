/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_browse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:06:49 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:54:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_tools_browse:
**		Call successively all node childrens
**		It do not change the node->children value
*/

long		sh_traverse_tools_browse(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	ptr = node->children;
	ret = SUCCESS;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (child->symbol->id != sh_index(IO_REDIRECT)
				|| context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		{
			if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
				break ;
			if (child->children
					&& (ret = sh_traverse_tools_browse(child, context)))
				break ;
		}
		ptr = ptr->next;
	}
	return (ret);
}

long		sh_traverse_tools_search(t_ast_node *node, int searched_symbol_id)
{
	t_list		*ptr;
	t_ast_node	*child;

	ptr = node->children;
	while (ptr != NULL)
	{
		child = (t_ast_node *)ptr->content;
		if (child->symbol->id == searched_symbol_id)
			return (SUCCESS);
		ptr = ptr->next;
	}
	return (ERROR);
}
