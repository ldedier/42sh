/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lr_automata.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:21:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 18:26:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** compute closure and transitions of a state via
** fixed point iteration
*/

int		sh_compute_state(t_state *state, t_lr_parser *parser)
{
	int changes;
	int ret;

	changes = 0;
	if ((ret = sh_compute_closure(state, parser)))
	{
		if (ret == -1)
			return (-1);
		changes |= 1;
	}
	if ((ret = sh_compute_transitions(state, parser)))
	{
		if (ret == -1)
			return (-1);
		changes |= 1;
	}
	return (changes);
}

/*
** compute all automata states and transitions via
** fixed point iteration method
*/

int		sh_compute_states(t_lr_parser *parser)
{
	t_list	*ptr;
	t_state	*state;
	int		changes;
	int		ret;

	ptr = parser->states;
	changes = 0;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		if ((ret = sh_compute_state(state, parser)))
		{
			if (ret == -1)
				return (-1);
			changes = 1;
		}
		ptr = ptr->next;
	}
	return (changes);
}

int		sh_compute_lr_automata(t_lr_parser *parser)
{
	t_state *first_state;
	int		ret;

	(void)ret;
	if (!(first_state = sh_compute_first_state(parser)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_compute_lr_automata (2)"));
	if (ft_lstaddnew_ptr_last_list(&parser->states, first_state,
			sizeof(t_state *), &parser->last_state_ptr))
	{
		sh_free_state(first_state, &parser->cfg);
		return (sh_perror(SH_ERR1_MALLOC, "sh_compute_lr_automata (2)"));
	}
	while ((ret = sh_compute_states(parser) == 1))
		;
	if (ret == -1)
		return (FAILURE);
	return (SUCCESS);
}
