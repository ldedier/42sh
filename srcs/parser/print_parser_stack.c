/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser_stack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:10:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:12:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_ast_builder(t_ast_builder *ast_builder, t_cfg *cfg)
{
	sh_print_symbol(ast_builder->symbol, cfg);
}

void	sh_print_stack_item(t_stack_item *stack_item, t_cfg *cfg)
{
	if (stack_item->stack_enum == E_STACK_STATE_INDEX)
		sh_print_state(stack_item->stack_union.state, -1, cfg);
	else
		sh_print_ast_builder(stack_item->stack_union.ast_builder, cfg);
}

void	sh_print_parser_state(t_lr_parser *parser, t_list *tokens)
{
	t_list			*ptr;

	ft_printf("input tokens:\n");
	sh_print_token_list(tokens, &parser->cfg);
	ft_printf("PDA stack:\n");
	ptr = parser->stack;
	while (ptr != NULL)
	{
		sh_print_stack_item(ptr->content, &parser->cfg);
		ptr = ptr->next;
	}
	ft_printf("\n");
}
