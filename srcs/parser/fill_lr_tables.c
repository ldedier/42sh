/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lr_tables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:19:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/09 19:07:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_fill_reduce(t_state *state, t_item *item, t_lr_parser *parser)
{
	int i;
	int end_of_input_index;

	end_of_input_index = sh_index(END_OF_INPUT);
	i = 0;
	while (i < NB_TERMS)
	{
		if (item->lookaheads[i])
		{
			if (item->production->from == &parser->cfg.start_symbol
					&& (i == end_of_input_index))
				parser->lr_tables[state->index][i].action_enum =
					E_ACTION_ACCEPT;
			else
			{
				parser->lr_tables[state->index]
					[i].action_enum = E_ACTION_REDUCE;
				parser->lr_tables[state->index]
					[i].action_union.production = item->production;
			}
		}
		i++;
	}
}

void	sh_fill_tables_by_transition(t_state *state, t_transition *transition,
			t_lr_parser *parser)
{
	parser->lr_tables[state->index][transition->symbol->id].action_enum =
		E_ACTION_SHIFT;
	parser->lr_tables[state->index][transition->symbol->id].
		action_union.state = transition->state;
}

void	sh_fill_tables_by_state(t_state *state, t_lr_parser *parser)
{
	t_list			*ptr;
	t_item			*item;
	t_transition	*transition;

	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->progress == NULL)
			sh_fill_reduce(state, item, parser);
		ptr = ptr->next;
	}
	ptr = state->transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)ptr->content;
		sh_fill_tables_by_transition(state, transition, parser);
		ptr = ptr->next;
	}
}

void	sh_fill_tables(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_fill_tables_by_state(state, parser);
		ptr = ptr->next;
	}
}
