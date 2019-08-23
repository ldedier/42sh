/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_transitions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 00:22:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/23 00:22:52 by ldedier          ###   ########.fr       */
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

t_state *sh_get_state_by_symbol(t_item *item, t_lr_parser *parser)
{
	t_list	*ptr;
	t_state *state;
	int		index;

//	ft_printf("index computation ..\n");
	index = hash_item_next(item) % parser->states_by_items->size;
//	ft_printf("%d\n", index);
	ptr = parser->states_by_items->data[index];
//	ptr = parser->states;//_by_items->data[index];
	//ft_printf("%d\n", ft_lstlen(ptr));
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
//		sh_print_state(state, -1);
//		ft_printf("\n");
		if (sh_is_eligible_for_transition(state, item))
		{
		//	ft_printf("WOOWOWLOLOL\n");
			return (state);
		}
		ptr = ptr->next;
	}
//	ft_printf("WOOWOW\n");
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

t_transition	*sh_new_transition(t_state *to, t_symbol *symbol)
{
	t_transition *res;

	if (!(res = (t_transition *)malloc(sizeof(t_transition))))
		return (NULL);
	res->state = to;
	res->symbol = symbol;
	return (res);
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

t_item	*sh_new_item_advance(t_item *item)
{
	t_item *res;

	if (!(res = (t_item *)malloc(sizeof(t_item))))
		return (NULL);
	res->production = item->production;
	res->progress = item->progress->next;
	res->lookahead = item->lookahead;
	res->parsed = 0;
	return (res);
}

t_state *sh_new_parser_state_from_item(t_item *item, t_lr_parser *parser)
{
	t_state *res;
	t_item	*new_item;

	if (!(res = sh_new_state()))
		return (NULL);
	if (!(new_item = sh_new_item_advance(item)))
	{
		free(res);
		return (NULL);
	}
	if (sh_add_item_to_state(parser, res, new_item))
	{
		free(new_item);
		free(res);
		return (NULL);
	}
	if (ft_lstaddnew_ptr_last_list(&parser->states,
		res, sizeof(t_state *), &parser->last_state_ptr))
	{
		sh_free_state(res);
		return (NULL);
	}
	return (res);
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
**
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
			if (!(res = sh_new_parser_state_from_item(item, parser))) //ajouter dans tout les cas done
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
