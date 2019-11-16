/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_term_ar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_term_ar(t_ast_node *node, t_context *context)
{
	t_ast_node	*middle_node;
	t_ast_node	*first_node;
	t_ast_node	*third_node;
	int			third_node_res;

	first_node = node->children->content;
	if (ft_lstlen(node->children) == 1)
		return (sh_traverse_arithmetic(first_node, context));
	middle_node = node->children->next->content;
	third_node = node->children->next->next->content;
	if (middle_node->symbol->id == LEX_TOK_AR_MULTIPLY)
		return (sh_traverse_arithmetic(first_node, context)
				* sh_traverse_arithmetic(third_node, context));
	third_node_res = sh_traverse_arithmetic(third_node, context);
	if (third_node_res == 0)
	{
		context->arithmetic_error = 1;
		return (1);
	}
	else if (middle_node->symbol->id == LEX_TOK_AR_DIVIDE)
		return (sh_traverse_arithmetic(first_node, context)
				/ third_node_res);
	else
		return (sh_traverse_arithmetic(first_node, context)
				% third_node_res);
	return (0);
}
