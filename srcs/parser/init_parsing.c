/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:40:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:56:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_init_parsing(t_lr_parser *parser, t_cfg_initializer *cfgi)
{
	parser->states = NULL;
	parser->last_state_ptr = NULL;
	parser->nb_states = -1;
	parser->lr_tables = NULL;
	parser->stack = NULL;
	if (!(parser->states_by_items = ft_hash_table_new(100000)))
		return (1);
	if (init_context_free_grammar(&parser->cfg, cfgi))
		return (1);
	if (sh_compute_lr_automata(parser))
		return (1);
	if (sh_compute_lr_tables(parser))
		return (1);
	return (0);
}

int			sh_init_parsing_posix(t_lr_parser *parser)
{
	t_cfg_initializer cfgi;

	cfgi.nb_symbols = NB_SYMBOLS;
	cfgi.nb_productions = NB_PRODUCTIONS;
	cfgi.nb_terms = NB_TERMS;
	cfgi.grammar_holder = g_grammar;
	cfgi.start_id = PROGRAM;
	cfgi.epsilon_index = sh_index(EPS);
	cfgi.eoi_index = sh_index(END_OF_INPUT);
	cfgi.index_func = &sh_index;
	g_glob.cfg = &parser->cfg;
	return (sh_init_parsing(parser, &cfgi));
}

static int	sh_identity(int value)
{
	return (value);
}

int			sh_init_parsing_arithmetic(t_lr_parser *parser)
{
	t_cfg_initializer cfgi;

	cfgi.nb_symbols = NB_SYMBOLS_AR;
	cfgi.nb_productions = NB_PRODUCTIONS_AR;
	cfgi.nb_terms = NB_TERMS_AR;
	cfgi.grammar_holder = g_ar_grammar;
	cfgi.start_id = ARITHMETIC_AR;
	cfgi.epsilon_index = EPS_AR;
	cfgi.eoi_index = END_OF_INPUT_AR;
	cfgi.index_func = &sh_identity;
	return (sh_init_parsing(parser, &cfgi));
}
