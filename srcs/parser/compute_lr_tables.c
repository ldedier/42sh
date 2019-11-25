/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_tables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:49:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 10:20:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_action	**sh_create_tables(t_lr_parser *parser)
{
	t_action	**res;
	int			i;
	int			j;

	parser->nb_states = ft_lstlen(parser->states);
	if (!(res = (t_action **)malloc(parser->nb_states * sizeof(t_action *))))
		return (NULL);
	i = 0;
	while (i < parser->nb_states)
	{
		if (!(res[i] = (t_action *)malloc(parser->cfg.nb_symbols
			* sizeof(t_action))))
		{
			while (--i >= 0)
				free(res[i]);
			free(res);
			return (NULL);
		}
		j = 0;
		while (j < parser->cfg.nb_symbols)
			res[i][j++].action_enum = E_ACTION_ERROR;
		i++;
	}
	return (res);
}

void		sh_fill_reduce(t_state *state, t_item *item, t_lr_parser *parser)
{
	if (parser->lr_tables[state->index]
			[item->lookahead->id].action_enum == E_ACTION_REDUCE)
		ft_printf("REDUCE REDUCE CONFLICT\n");
	else if (parser->lr_tables[state->index]
			[item->lookahead->id].action_enum == E_ACTION_SHIFT)
		ft_printf("SHIFT REDUCE CONFLICT\n");
	if (item->production->from == &parser->cfg.start_symbol
			&& (item->lookahead->id == parser->cfg.eoi_index))
		parser->lr_tables[state->index][parser->cfg.eoi_index].action_enum =
			E_ACTION_ACCEPT;
	else
	{
		parser->lr_tables[state->index]
			[item->lookahead->id].action_enum = E_ACTION_REDUCE;
		parser->lr_tables[state->index]
			[item->lookahead->id].action_union.production = item->production;
	}
}

void		sh_fill_tables_by_transition(t_state *state,
		t_transition *transition, t_lr_parser *parser)
{
	if (parser->lr_tables[state->index]
			[transition->symbol->id].action_enum == E_ACTION_REDUCE)
	{
		ft_printf("SHIFT REDUCE CONFLICT\n");
		ft_printf("(%d)\n", transition->symbol->id);
		ft_printf("for symbol: ");
		sh_print_symbol(transition->symbol, &parser->cfg);
		ft_printf("\n");
		sh_print_state(state, 0, &parser->cfg);
		ft_printf("before:\n");
		sh_print_production(parser->lr_tables[state->index]
			[transition->symbol->id].action_union.production, &parser->cfg);
		ft_printf("after:\n");
		sh_print_state(transition->state, 0, &parser->cfg);
	}
	else if (parser->lr_tables[state->index]
			[transition->symbol->id].action_enum == E_ACTION_SHIFT)
		ft_printf("SHIFT SHIFT CONFLICT\n");
	parser->lr_tables[state->index]
		[transition->symbol->id].action_enum = E_ACTION_SHIFT;
	parser->lr_tables[state->index]
		[transition->symbol->id].action_union.state = transition->state;
}

void		sh_fill_tables_by_state(t_state *state, t_lr_parser *parser)
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

int			sh_compute_lr_tables(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;

	if (!(parser->lr_tables = sh_create_tables(parser)))
		return (1);
	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_fill_tables_by_state(state, parser);
		ptr = ptr->next;
	}
	return (0);
}
