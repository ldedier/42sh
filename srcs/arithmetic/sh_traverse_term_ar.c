/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_term_ar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:48:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:53:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static long	sh_traverse_term_ar_operand(t_ast_node *node,
	t_context *context, t_ast_node *first_node)
{
	t_ast_node	*middle_node;
	t_ast_node	*third_node;
	long		third_node_res;

	middle_node = node->children->next->content;
	third_node = node->children->next->next->content;
	if (middle_node->symbol->id == LEX_TOK_AR_MULTIPLY)
	{
		return (sh_traverse_arithmetic(first_node, context) *
			sh_traverse_arithmetic(third_node, context));
	}
	third_node_res = sh_traverse_arithmetic(third_node, context);
	if (third_node_res == 0)
		return (sh_throw_ar_error(context, SH_ERR1_DIV_ZERO, 1));
	else if (middle_node->symbol->id == LEX_TOK_AR_DIVIDE)
		return (sh_traverse_arithmetic(first_node, context)
				/ third_node_res);
	else
	{
		return (sh_traverse_arithmetic(first_node, context)
				% third_node_res);
	}
	return (0);
}

long		sh_traverse_term_ar(t_ast_node *node, t_context *context)
{
	t_ast_node	*first_node;

	first_node = node->children->content;
	if (ft_lstlen(node->children) == 1)
		return (sh_traverse_arithmetic(first_node, context));
	return (sh_traverse_term_ar_operand(node, context, first_node));
}
