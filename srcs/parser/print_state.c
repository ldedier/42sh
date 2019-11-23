/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:07:33 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:07:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_item(t_item *item, t_cfg *cfg)
{
	t_list		*ptr;
	t_symbol	*symbol;

	sh_print_symbol(item->production->from, cfg);
	ft_printf(" → ");
	ptr = item->production->symbols;
	while (ptr != NULL)
	{
		if (ptr == item->progress)
			ft_printf("%s·%s", BOLD, EOC);
		symbol = (t_symbol *)ptr->content;
		sh_print_symbol(symbol, cfg);
		ptr = ptr->next;
	}
	if (ptr == item->progress)
		ft_printf("%s·%s", BOLD, EOC);
	ft_printf("\t(for symbol: [");
	sh_print_symbol(item->lookahead, cfg);
	ft_printf("])\n");
}

void	sh_print_transition(t_transition *transition, t_cfg *cfg, int depth)
{
	(void)depth;
	sh_print_symbol(transition->symbol, cfg);
	ft_printf(" → ");
	sh_print_state(transition->state, -1, cfg);
	ft_printf("\n");
}

void	print_state_transitions(t_state *state, int depth, t_cfg *cfg)
{
	t_list			*ptr;
	t_transition	*transition;

	if (depth > 0)
	{
		ft_printf("%s\nState transitions:%s \n\n%s", UNDERLINE, EOC);
		ptr = state->transitions;
		while (ptr != NULL)
		{
			transition = (t_transition *)ptr->content;
			sh_print_transition(transition, cfg, depth - 1);
			ptr = ptr->next;
		}
	}
}

void	sh_print_state(t_state *state, int depth, t_cfg *cfg)
{
	t_list			*ptr;
	t_item			*item;

	if (depth == -1)
	{
		ft_printf("%sS%d%s", YELLOW, state->index, EOC);
		return ;
	}
	ft_printf("%sState #%d\n\n%s", YELLOW, state->index, EOC);
	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		sh_print_item(item, cfg);
		ptr = ptr->next;
	}
	print_state_transitions(state, depth, cfg);
}
