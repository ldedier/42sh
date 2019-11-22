/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_closure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:38:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:24:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_closure_from_symbol_index(int i, int *changes,
		t_state *state, t_lr_parser *parser)
{
	t_list			*ptr;
	t_production	*production;

	ptr = parser->tmp_item->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		if (!sh_is_in_state_item(production, state,
					&parser->cfg.symbols[i]))
		{
			if (sh_process_add_to_closure(production, state,
						&parser->cfg.symbols[i], parser))
				return (-1);
			*changes = 1;
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}

int		sh_add_to_closure(t_state *state,
			t_symbol *new_item, char *first_sets, t_lr_parser *parser)
{
	int				changes;
	int				i;

	changes = 0;
	i = 0;
	parser->tmp_item = new_item;
	while (i < parser->cfg.nb_terms)
	{
		if (first_sets[i])
		{
			if (sh_add_closure_from_symbol_index(i, &changes, state, parser))
				return (-1);
		}
		i++;
	}
	return (changes);
}

/*
** If A → α · Bω [t] is in the state, add B → · γ [t]
** to the state for each production B → γ and for
** each terminal t ∈ FIRST*(ω t)
**
**
**		w_ptr				=>	ω
**		next_non_terminal	=>	B
**		item->lookahead		=>	t
*/

int		sh_process_compute_closure_item(t_item *item, t_state *state,
			t_lr_parser *parser)
{
	t_symbol	*next_non_terminal;
	t_list		*w_ptr;
	int			ret;
	int			changes;
	char		*first_sets;

	if (!(first_sets = malloc(parser->cfg.nb_terms)))
		return (1);
	changes = 0;
	if ((next_non_terminal = sh_get_next_non_terminal(item, &w_ptr)))
	{
		sh_compute_first_sets_str_append(first_sets, &parser->cfg,
			w_ptr, item->lookahead);
		if ((ret = sh_add_to_closure(state, next_non_terminal,
				first_sets, parser)))
		{
			if (ret == -1)
				return (ft_free_turn(first_sets, -1));
			changes = 1;
		}
	}
	item->parsed = !changes;
	free(first_sets);
	return (changes);
}

int		sh_process_compute_closure(t_state *state, t_lr_parser *parser)
{
	int		changes;
	t_list	*ptr;
	t_item	*item;
	int		ret;

	changes = 0;
	ptr = state->items;
	while (ptr != NULL)
	{
		item = (t_item *)ptr->content;
		if (!item->parsed && (ret = sh_process_compute_closure_item(item,
			state, parser)))
		{
			if (ret == -1)
				return (-1);
			changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_compute_closure(t_state *state, t_lr_parser *parser)
{
	int ret;
	int changes;

	changes = 0;
	while ((ret = sh_process_compute_closure(state, parser)) == 1)
		changes = 1;
	if (ret == -1)
		return (-1);
	return (changes);
}
