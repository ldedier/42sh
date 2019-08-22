/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_automata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:21:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/05 11:21:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** compute closure and transitions of a state via
** fixed point iteration
*/

int		sh_compute_state(t_state *state, t_lr_parser *parser)
{
	if (sh_compute_closure(state, parser) == -1) //to opti: don't check all items
		return (-1);
	if (sh_compute_transitions(state, parser) == -1) //to opti don't check all items
		return (-1);
	return (0);
}

/*
** compute all automata states and transitions via
** fixed point iteration method
*/

int		sh_compute_states(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;

	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if (sh_compute_state(state, parser) == -1)
			return (-1);
		ptr = ptr->next;
	}
	return (0);
}

int		sh_compute_lr_automata(t_lr_parser *parser)
{
	t_state *first_state;
	int		ret;

	(void)ret;
	if (!(first_state = sh_compute_first_state(parser)))
		return (1);
	if (ft_lstaddnew_ptr(&parser->states, first_state, sizeof(t_state *)))
	{
		sh_free_state(first_state);
		return (1);
	}
	return (sh_compute_states(parser));
}
