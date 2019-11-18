/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_transitions_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:30:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:32:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_eligible_for_transition(t_state *state, t_item *item)
{
	t_list *ptr;
	t_item *item_ptr;

	ptr = state->items_by_productions[item->production->index];
	while (ptr != NULL)
	{
		item_ptr = (t_item *)ptr->content;
		if (item_ptr->lookahead == item->lookahead &&
				item->progress->next == item_ptr->progress)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_state	*sh_get_state_by_symbol(t_item *item, t_lr_parser *parser)
{
	t_list	*ptr;
	t_state *state;
	int		index;

	index = hash_item_next(item) % parser->states_by_items->size;
	ptr = parser->states_by_items->data[index];
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if (sh_is_eligible_for_transition(state, item))
			return (state);
		ptr = ptr->next;
	}
	return (NULL);
}

t_state	*sh_get_state_by_transition(t_state *state, t_symbol *symbol)
{
	t_list			*ptr;
	t_transition	*transition;

	ptr = state->transitions;
	while (ptr != NULL)
	{
		transition = (t_transition *)ptr->content;
		if (transition->symbol == symbol)
			return (transition->state);
		ptr = ptr->next;
	}
	return (NULL);
}

int		sh_add_transition(t_state *from, t_state *to, t_symbol *symbol)
{
	t_transition *transition;

	if (!(transition = sh_new_transition(to, symbol)))
		return (1);
	if (ft_lstaddnew_ptr(&from->transitions,
				transition, sizeof(t_transition)))
	{
		free(transition);
		return (1);
	}
	return (0);
}

int		sh_is_in_state_progress_item(t_state *state, t_item *item)
{
	t_list *ptr;
	t_item *item_ptr;

	ptr = state->items_by_productions[item->production->index];
	while (ptr != NULL)
	{
		item_ptr = (t_item *)ptr->content;
		if (item_ptr->lookahead == item->lookahead &&
				item->progress->next == item_ptr->progress)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
