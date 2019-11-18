/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_transitions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 00:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:33:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_to_state_check(t_state *state, t_item *item,
			int *changes, t_lr_parser *parser)
{
	t_item *new_item;

	if (sh_is_in_state_progress_item(state, item))
		return (0);
	else
	{
		if (!(new_item = sh_new_item_advance(item)))
			return (1);
		if (sh_add_item_to_state(parser, state, new_item))
		{
			free(new_item);
			return (1);
		}
		*changes = 1;
		return (0);
	}
}

/*
** gets the state where the transition leads to for this item and creates the
** transition or both the state and the transition if necessary
** then add the convenient item as necessary in the given state
*/

int		sh_add_transition_item(t_item *item,
			t_state *state, t_lr_parser *parser, int *changes)
{
	t_state *res;

	if ((res = sh_get_state_by_transition(state,
			(t_symbol *)item->progress->content)))
	{
		if (sh_add_to_state_check(res, item, changes, parser))
			return (1);
		return (0);
	}
	else
	{
		if (!(res = sh_get_state_by_symbol(item, parser)))
		{
			if (!(res = sh_new_parser_state_from_item(item, parser)))
				return (1);
		}
		if (sh_add_transition(state, res, item->progress->content))
			return (1);
		*changes = 1;
		return (0);
	}
}

int		sh_compute_transitions(t_state *state, t_lr_parser *parser)
{
	t_list		*ptr;
	t_item		*item;
	int			changes;

	ptr = state->items;
	changes = 0;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->progress && sh_add_transition_item(item, state,
				parser, &changes))
			return (-1);
		ptr = ptr->next;
	}
	return (changes);
}
