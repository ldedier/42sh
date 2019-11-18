/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_comparison_ar.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:47:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 12:04:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static long	sh_traverse_comparison_ar_operand(t_ast_node *first_node,
		t_ast_node *middle_node, t_ast_node *third_node, t_context *context)
{
	if (middle_node->symbol->id == LEX_TOK_AR_GREAT)
		return (sh_traverse_arithmetic(first_node, context)
			> sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_GREATEQ)
		return (sh_traverse_arithmetic(first_node, context)
			>= sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_LESS)
		return (sh_traverse_arithmetic(first_node, context)
			< sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_LESSEQ)
		return (sh_traverse_arithmetic(first_node, context)
			<= sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_EQUAL)
		return (sh_traverse_arithmetic(first_node, context)
			== sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_NOT_EQUAL)
	{
		return (sh_traverse_arithmetic(first_node, context)
			!= sh_traverse_arithmetic(third_node, context));
	}
	return (0);
}

long		sh_traverse_comparison_ar(t_ast_node *node, t_context *context)
{
	t_ast_node *middle_node;
	t_ast_node *first_node;
	t_ast_node *third_node;

	first_node = node->children->content;
	if (ft_lstlen(node->children) == 1)
		return (sh_traverse_arithmetic(first_node, context));
	middle_node = node->children->next->content;
	third_node = node->children->next->next->content;
	return (sh_traverse_comparison_ar_operand(first_node,
		middle_node, third_node, context));
}
