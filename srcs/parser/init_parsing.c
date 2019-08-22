/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:40:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/09 19:07:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_init_parsing(t_lr_parser *parser)
{
	g_glob.cfg = &parser->cfg;
	parser->ast_root = NULL;
	parser->cst_root = NULL;
	parser->states = NULL;
	parser->nb_states = -1;
	parser->lr_tables = NULL;
	parser->stack = NULL;
	parser->tokens = NULL;
	if (init_context_free_grammar(&parser->cfg))
		return (1);
	if (sh_compute_lr_automata(parser))
		return (1);
	if (sh_compute_lr_tables(parser))
		return (1);
//	sh_free_lr_automata(parser);
	return (0);
}
