/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:50:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_prod(t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...)
{
	va_list		ap;
	int			symbol_index;
	int			i;
	static int	index = 0;

	if (ft_lstaddnew_ptr_last(&symbol->productions,
			&cfg->productions[index], sizeof(t_production *)))
		return (1);
	va_start(ap, nb_symbols);
	cfg->productions[index].symbols = NULL;
	cfg->productions[index].from = symbol;
	cfg->productions[index].index = index;
	i = 0;
	while (i < nb_symbols)
	{
		symbol_index = sh_index(va_arg(ap, int));
		if (ft_lstaddnew_ptr_last(&cfg->productions[index].symbols,
					&cfg->symbols[symbol_index], sizeof(t_symbol *)))
			return (1);
		i++;
	}
	index++;
	va_end(ap);
	return (0);
}

int		init_start_symbol(t_cfg *cfg, t_symbol *symbol)
{
	symbol->id = cfg->nb_symbols + 1;
	symbol->productions = NULL;
	sh_add_prod(symbol, cfg, 1, PROGRAM);
	ft_strcpy(symbol->debug, "S");
	return (0);
}

int		init_symbol(t_symbol *symbol, t_cfg *cfg, int index)
{
	int i;

	if (!(symbol->first_sets = malloc(sizeof(char) * cfg->nb_terms)))
		return (1);
	if (!(symbol->follow_sets = malloc(sizeof(char) * cfg->nb_terms)))
	{
		free(symbol->first_sets);
		return (1);
	}
	i = 0;
	while (i < cfg->nb_terms)
	{
		symbol->first_sets[i] = 0;
		symbol->follow_sets[i] = 0;
		i++;
	}
	symbol->productions = NULL;
	symbol->id = index;
	symbol->relevant = cfg->grammar_holder[index].relevant;
	symbol->replacing = cfg->grammar_holder[index].replacing;
	ft_strcpy(symbol->debug, cfg->grammar_holder[index].debug);
	return (0);
}

int		init_context_free_grammar(t_cfg *cfg, t_cfg_initializer *cfgi)
{
	int i;

	cfg->nb_symbols = cfgi->nb_symbols;
	cfg->nb_productions = cfgi->nb_productions;
	cfg->nb_terms = cfgi->nb_terms;
	cfg->nb_noterms = cfgi->nb_symbols - cfgi->nb_terms;
	cfg->grammar_holder = cfgi->grammar_holder;
	if (!(cfg->productions = (t_production *)malloc(sizeof(t_production) * cfg->nb_productions)))
		return (1);
	if (!(cfg->symbols = (t_symbol *)malloc(sizeof(t_symbol) * cfg->nb_symbols)))
	{
		free(cfg->productions);
		return (1);
	}
	init_start_symbol(cfg, &cfg->start_symbol);
	i = 0;
	while (i < cfg->nb_symbols)
	{
		init_symbol(&cfg->symbols[i], cfg, i);
		i++;
	}
	i = cfg->nb_terms;
	while (i < cfg->nb_symbols)
	{
		if (cfg->grammar_holder[i].init_prod(cfg, &cfg->symbols[i]))
			return (1);
		i++;
	}
	if (sh_compute_first_sets(cfg))
		return (1);
	return (0);
}
