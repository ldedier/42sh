/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:14:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:48:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
void	sh_free_stack_item(t_stack_item *stack_item)
{
	if (stack_item->stack_enum == E_STACK_AST_BUILDER)
		sh_free_ast_builder(stack_item->stack_union.ast_builder);
	free(stack_item);
}
*/

void	sh_free_stack_item_light(t_stack_item *stack_item)
{
	if (stack_item->stack_enum == E_STACK_AST_BUILDER)
		free(stack_item->stack_union.ast_builder);
	free(stack_item);
}

void	sh_free_stack_item(t_stack_item *stack_item)
{
	if (stack_item->stack_enum == E_STACK_AST_BUILDER)
		sh_free_ast_builder(stack_item->stack_union.ast_builder);
	free(stack_item);
}

void	sh_free_stack_item_lst(void *si, size_t dummy)
{
	(void)dummy;
	sh_free_stack_item((t_stack_item *)si);
}

void	sh_free_stack_item_lst_light(void *si, size_t dummy)
{
	(void)dummy;
	sh_free_stack_item_light((t_stack_item *)si);
}


void	free_state_lst(void *s, size_t dummy)
{
	(void)dummy;
	sh_free_state((t_state *)s);
}

void	sh_free_lr_automata(t_lr_parser *parser)
{
	ft_lstdel(&parser->states, free_state_lst);
}

void	sh_free_production(void *p, size_t dummy)
{
	t_production *production;

	(void)dummy;
	production = (t_production *)p;
	ft_lstdel_ptr(&production->symbols);
}
