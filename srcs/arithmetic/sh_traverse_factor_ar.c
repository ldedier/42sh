/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_factor_ar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:49:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	add_shell_var(char *variable, int to_add, t_context *context)
{
	long res;
	char *to_store;

	res = get_integer_from_var(variable, context);
	res += to_add;
	if (!(to_store = ft_ltoa(res, 10)))
	{
		sh_perror(SH_ERR1_MALLOC, "add_shell_var");
		context->arithmetic_error = 2;
		return ;
	}
	if (sh_vars_assign_key_val(context->shell->env,
		context->shell->vars, variable, to_store))
	{
		free(to_store);
		sh_perror(SH_ERR1_MALLOC, "add_shell_var");
		context->arithmetic_error = 2;
	}
}

long	get_integer_from_var(char *variable, t_context *context)
{
	char *res;

	if (!(res = sh_vars_get_value(context->shell->env,
		context->shell->vars, variable)))
	{
		return (0);
	}
	else
		return (ft_atol(res));
}

static long sh_traverse_add_factor(t_ast_node *first_child,
		t_ast_node *second_child, t_context *context)
{
	int			ret;

	if (second_child->symbol->id == LEX_TOK_AR_VARIABLE)
	{
		add_shell_var(second_child->token->value,
			first_child->symbol->id == LEX_TOK_AR_DEC ? -1 : 1, context);
		return (get_integer_from_var(first_child->token->value, context));
	}
	else
	{
		ret = get_integer_from_var(first_child->token->value, context);
		add_shell_var(first_child->token->value,
			second_child->symbol->id == LEX_TOK_AR_DEC ? -1 : 1, context);
		return (ret);
	}
}

long		sh_traverse_factor_ar(t_ast_node *node, t_context *context)
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
		return (sh_traverse_add_factor(first_child,
			second_child, context));
	}
}
