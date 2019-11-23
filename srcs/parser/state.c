/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:34:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

unsigned long	hash_item_next(void *i)
{
	t_item			*item;
	unsigned long	res;

	res = 5381;
	item = (t_item *)i;
	res += (unsigned long)item->lookahead * 2
			+ (unsigned long)item->production * 10
				+ (unsigned long)item->progress->next;
	return (res);
}

unsigned long	hash_item(void *i)
{
	t_item			*item;
	unsigned long	res;

	res = 5381;
	item = (t_item *)i;
	res += (unsigned long)item->lookahead * 2
			+ (unsigned long)item->production * 10
				+ (unsigned long)item->progress;
	return (res);
}

int				sh_add_item_to_state(t_lr_parser *parser,
	t_state *state, t_item *item)
{
	if (ft_lstaddnew_ptr(&state->items_by_productions
		[item->production->index],
			item, sizeof(t_item *)))
		return (1);
	if (ft_lstaddnew_ptr_last_list(&state->items, item,
			sizeof(t_item *), &state->last_item_ptr))
		return (1);
	if (ft_hash_table_add(parser->states_by_items, state, item, hash_item))
		return (1);
	return (0);
}

t_state			*sh_new_state(t_cfg *cfg)
{
	t_state		*res;
	int			i;

	if (!(res = (t_state *)malloc(sizeof(t_state))))
		return (NULL);
	res->transitions = NULL;
	res->items = NULL;
	res->last_item_ptr = NULL;
	res->index = cfg->state_index++;
	i = 0;
	while (i < cfg->nb_productions)
		res->items_by_productions[i++] = NULL;
	return (res);
}

void			sh_free_state(t_state *state, t_cfg *cfg)
{
	int i;

	ft_lstdel_value(&state->items);
	ft_lstdel_value(&state->transitions);
	i = 0;
	while (i < cfg->nb_productions)
		ft_lstdel_ptr(&state->items_by_productions[i++]);
	free(state);
	state = NULL;
}
