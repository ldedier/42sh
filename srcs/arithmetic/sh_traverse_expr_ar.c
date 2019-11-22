/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_expr_ar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:47:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:57:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

long		sh_traverse_expr_ar(t_ast_node *node, t_context *context)
{
	t_ast_node *middle_node;
	t_ast_node *first_node;
	t_ast_node *third_node;

	first_node = node->children->content;
	if (ft_lstlen(node->children) == 1)
		return (sh_traverse_arithmetic(first_node, context));
	middle_node = node->children->next->content;
	third_node = node->children->next->next->content;
	if (middle_node->symbol->id == LEX_TOK_AR_PLUS)
		return (sh_traverse_arithmetic(first_node, context)
				+ sh_traverse_arithmetic(third_node, context));
	else if (middle_node->symbol->id == LEX_TOK_AR_MINUS)
	{
		return (sh_traverse_arithmetic(first_node, context)
				- sh_traverse_arithmetic(third_node, context));
	}
	return (0);
}
