/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_closure_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:08:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:10:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_is_in_state_item(t_production *production,
				t_state *state, t_symbol *lookahead)
{
	t_list	*ptr;
	t_item	*item;

	ptr = state->items_by_productions[production->index];
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (item->lookahead == lookahead
			&& item->progress == item->production->symbols)
		{
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

t_item		*sh_new_item(t_production *production,
				t_symbol *lookahead)
{
	t_item	*res;

	if (!(res = malloc(sizeof(t_item))))
		return (NULL);
	res->production = production;
	res->progress = production->symbols;
	res->lookahead = lookahead;
	res->parsed = 0;
	return (res);
}

int			sh_process_add_to_closure(t_production *production,
				t_state *state, t_symbol *lookahead, t_lr_parser *parser)
{
	t_item *item;

	if (!(item = sh_new_item(production, lookahead)))
		return (-1);
	if (sh_add_item_to_state(parser, state, item))
	{
		free(item);
		return (-1);
	}
	return (0);
}

t_symbol	*sh_get_next_non_terminal(t_item *item, t_list **w_ptr)
{
	t_symbol *res;

	if (item->progress == NULL)
		return (NULL);
	else
	{
		res = (t_symbol *)item->progress->content;
		*w_ptr = item->progress->next;
		return (res);
	}
}

void		sh_compute_first_sets_str_append(char *first_sets, t_cfg *cfg,
		t_list *w, t_symbol *append)
{
	t_list		*ptr;
	int			i;
	t_symbol	*symbol;

	i = 0;
	while (i < cfg->nb_terms)
		first_sets[i++] = 0;
	ptr = w;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)ptr->content;
		sh_process_transitive_first_sets_2(first_sets, symbol, cfg);
		if (!symbol->first_sets[cfg->epsilon_index])
			return ;
		ptr = ptr->next;
	}
	sh_process_transitive_first_sets_2(first_sets, append, cfg);
	if (!append->first_sets[cfg->epsilon_index])
		return ;
	sh_process_transitive_first_set_2(first_sets, cfg->epsilon_index);
}
