/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_transitions_allocate.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:33:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:34:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_transition	*sh_new_transition(t_state *to, t_symbol *symbol)
{
	t_transition *res;

	if (!(res = (t_transition *)malloc(sizeof(t_transition))))
		return (NULL);
	res->state = to;
	res->symbol = symbol;
	return (res);
}

t_item			*sh_new_item_advance(t_item *item)
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

t_state			*sh_new_parser_state_from_item(t_item *item,
	t_lr_parser *parser)
{
	t_state *res;
	t_item	*new_item;

	if (!(res = sh_new_state(&parser->cfg)))
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
		sh_free_state(res, &parser->cfg);
		return (NULL);
	}
	return (res);
}
