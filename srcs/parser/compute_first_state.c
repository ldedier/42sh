/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_first_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:21:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/22 16:34:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_state	*sh_compute_first_state(t_lr_parser *parser)
{
	t_state *first_state;
	t_item	*first_item;

	if (!(first_state = sh_new_state(&parser->cfg)))
		return (NULL);
	if (!(first_item =
			sh_new_item(parser->cfg.start_symbol.productions->content,
				&parser->cfg.symbols[sh_index(END_OF_INPUT)])))
	{
		free(first_state);
		return (NULL);
	}
	if (sh_add_item_to_state(parser, first_state, first_item))
	{
		//free
		return (NULL);
	}
	return (first_state);
}
