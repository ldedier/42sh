/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/12 15:02:18 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * get_separator_op :
 * This function take the current and_or nod to execute and the separator_op.
 * Separator_op is necessary because it can change the way we execute the
 * and_or node.
 * semi column separator : just execute the and_or
 * and (&) separator : probably we need to fork at this time and execute
 * and_or node in back_ground.
*/
static int 	get_separator_op(
	t_ast_node *to_execute, t_ast_node *separator, t_context *context)
{
	//need to send to_execute to the good separator
	(void)separator;
	if (separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
		return (sh_traverse_semicol(to_execute, context));
	if (separator->symbol->id == sh_index(LEX_TOK_AND))
	{
		ft_dprintf(STDERR_FILENO, "sh_traverse_list: sorry & is not yet implement\n");
		return (ERROR);
	}
	return (FAILURE);
}

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
			if ((ret = get_separator_op(
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
