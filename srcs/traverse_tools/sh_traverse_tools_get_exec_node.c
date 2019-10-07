/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_get_exec_node.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:00:19 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/07 16:02:30 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * get_node_to_exec :
 * This function look over the t_list of LIST (grammar) content.
 * If we find a and_or (grammar) sequence follow by a separator, we execute
 * get_separator_op wich dispatch the execution of the and_or node between
 * the different separator found.
 *
 * If they are no separator, we just call the next level on the ast,
 * and_or browser (sh_traverse_and_or)
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
			ret = f(node_to_exec, curr_node->children->content, context);
			node_to_exec = NULL;
		}
		else
			node_to_exec = curr_node;
		lst = lst->next;
	}
	if (node_to_exec && ret == SUCCESS)
		ret = sh_traverse_and_or(node_to_exec, context);
	return (ret);
}

