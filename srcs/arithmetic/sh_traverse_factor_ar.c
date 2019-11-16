/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_factor_ar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:49:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 17:49:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	increment_shell_var(char *variable, t_context *context)
{
	(void)variable;
	(void)context;
}

int		get_integer_from_var(char *variable, t_context *context)
{
	(void)variable;
	(void)context;
	return (0);
}

static int sh_traverse_incremented_factor(t_ast_node *first_child,
		t_ast_node *second_child, t_context *context)
{
	int			ret;

	if (second_child->symbol->id == LEX_TOK_AR_INC)
	{
		ret = get_integer_from_var(first_child->token->value, context);
		increment_shell_var(first_child->token->value, context);
		return (ret);
	}
	else
	{
		increment_shell_var(second_child->token->value, context);
		return (get_integer_from_var(first_child->token->value, context));
	}
}

int		sh_traverse_factor_ar(t_ast_node *node, t_context *context)
{
	t_ast_node	*first_child;
	t_ast_node	*second_child;

	first_child = (t_ast_node *)node->children->content;
	if (ft_lstlen(node->children) == 1)
	{
		if (first_child->symbol->id == LEX_TOK_AR_INTEGER)
			return (first_child->token->token_union.ival);
		else
			return (get_integer_from_var(first_child->token->value, context));
	}
	else
	{
		second_child = (t_ast_node *)node->children->next->content;
		return (sh_traverse_incremented_factor(first_child,
			second_child, context));
	}
}
