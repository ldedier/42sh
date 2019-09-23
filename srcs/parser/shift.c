/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/11 11:06:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_process_shift_adds_stack_item(t_lr_parser *parser,
			t_stack_item *stack_item_ast_builder,
				t_stack_item *stack_item_state)
{
	if (ft_lstaddnew_ptr(&parser->stack,
		stack_item_ast_builder, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item_state);
		sh_free_stack_item(stack_item_ast_builder);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	if (ft_lstaddnew_ptr(&parser->stack,
		stack_item_state, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item_state);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	return (SUCCESS);
}

int		sh_process_shift_adds(t_lr_parser *parser,
			t_ast_builder *ast_builder, t_state *state)
{
	t_stack_item *stack_item_ast_builder;
	t_stack_item *stack_item_state;

	if (!(stack_item_state = new_stack_item(NULL, state)))
	{
		sh_free_ast_builder(ast_builder);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	if (!(stack_item_ast_builder = new_stack_item(ast_builder, 0)))
	{
		sh_free_ast_builder(ast_builder);
		sh_free_stack_item(stack_item_state);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_shift_adds"));
	}
	return (sh_process_shift_adds_stack_item(parser, stack_item_ast_builder,
		stack_item_state));
}

int		sh_process_shift(t_list **tokens, t_state *state, t_lr_parser *parser)
{
	t_token			*token;
	t_ast_builder	*ast_builder;

	token = ft_lstpop_ptr(tokens);
	if (!(ast_builder = sh_new_ast_builder(token,
			&parser->cfg.symbols[token->index])))
	{
		t_token_free(token);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_shift"));
	}
	if (sh_process_shift_adds(parser, ast_builder, state) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
