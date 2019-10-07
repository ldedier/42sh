/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/07 14:46:54 by jdugoudr         ###   ########.fr       */
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
static int 	get_node_to_exec(t_ast_node *node, t_context *context)
{
	t_list 		*lst;
	t_ast_node	*curr_node;
	t_ast_node	*node_to_exec;
	int 		ret;

	lst = node->children;
	node_to_exec = NULL;
	ret = SUCCESS;
	while (lst)
	{
		curr_node = lst->content;
		if (curr_node->symbol->id == sh_index(SEPARATOR_OP))
		{
			if ((ret = sh_get_separator_op(
				node_to_exec, curr_node->children->content, context)))
				return (ret);
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

/*
 * sh_traverse_list :
 * This is the browser of the t_list LIST (grammar)
 * Here we scan all LIST node, and_or and separator together, and
 * execute the and_or node at the moment we find it.
 * We wait its return to continue to run the t_list LIST.
*/
int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int		ret;

	sh_traverse_tools_show_traverse_start(node, context);
	ret = get_node_to_exec(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	if (ret == FAILURE)
		return (FAILURE);
	else if (ret == STOP_CMD_LINE)
		return (ERROR);
	return (ret);
}
