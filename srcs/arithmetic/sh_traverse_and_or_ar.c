/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or_ar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:44:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 14:27:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static long	sh_traverse_and_or_ar_operand(t_ast_node *node, t_context *context)
{
	t_ast_node	*middle_node;
	long		first;

	middle_node = (t_ast_node *)node->children->next->content;
	first = sh_traverse_arithmetic(node->children->content, context);
	if (middle_node->symbol->id == LEX_TOK_AR_AND)
	{
		if (first)
			return (first
					&& sh_traverse_arithmetic(node->children->
						next->next->content, context));
		else
			return (0);
	}
	else
	{
		if (!first)
			return (!first
					|| sh_traverse_arithmetic(node->children->
						next->next->content, context));
		else
			return (1);
	}
}

long		sh_traverse_and_or_ar(t_ast_node *node, t_context *context)
{
	if (ft_lstlen(node->children) == 1)
		return (sh_traverse_arithmetic(node->children->content, context));
	else
		return (sh_traverse_and_or_ar_operand(node, context));
}
