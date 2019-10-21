/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:49:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/15 12:03:59 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * sh_traverse_list :
 * This is the browser of the t_list LIST (grammar)
 * Here we scan all LIST node, and_or and separator together, and
 * execute the and_or node at the moment we find it.
 * We wait its return to continue to run the t_list LIST.
*/
int			sh_traverse_list(t_ast_node *node, t_context *context)
{
	int			ret;
	t_ast_node	*last_separator;

	if (node->children->next)
	{
		last_separator = node->children->next->content;
		last_separator = last_separator->children->content;
		/*ft_printf("we've got a separator ! it's ");// delete it*/
		if (last_separator->symbol->id == sh_index(LEX_TOK_AND))
			;
			/*ft_printf("-%c-\n", '&');// delete it*/
		else if (last_separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
			;
			/*ft_printf("-%c-\n", ';');// delete it*/
		else
			return (ERROR);
			/*ft_printf("-... well this is not suppose to append...-\n");// delete it*/
	}
	sh_traverse_tools_show_traverse_start(node, context);
	ret = get_node_to_exec(node->children->content, context, SEPARATOR_OP, &sh_get_separator_op);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	if (ret == FAILURE)
		return (FAILURE);
	else if (ret == STOP_CMD_LINE)
		return (ERROR);
	return (ret);
}
