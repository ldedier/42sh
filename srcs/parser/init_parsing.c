/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:40:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/22 16:52:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_parsing(t_lr_parser *parser)
{
	g_glob.cfg = &parser->cfg;
	parser->states = NULL;
	parser->last_state_ptr = NULL;
	parser->nb_states = -1;
	parser->lr_tables = NULL;
	parser->stack = NULL;
	if (!(parser->states_by_items = ft_hash_table_new(100000)))
		return (1);
	if (init_context_free_grammar(&parser->cfg))
		return (1);
	if (sh_compute_lr_automata(parser))
		return (1);
	if (sh_compute_lr_tables(parser))
		return (1);
//	ft_hash_table_show_perf(parser->states_by_items);
	return (0);
}
