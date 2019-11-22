/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stack_item.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:25:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:25:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
