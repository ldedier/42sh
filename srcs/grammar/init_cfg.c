/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cfg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:27:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:27:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_prod(t_symbol *symbol, t_cfg *cfg, int nb_symbols, ...)
{
	va_list			ap;
	int				symbol_index;
	t_production	*prod;
	int				i;

	prod = &cfg->productions[cfg->prod_index];
	if (ft_lstaddnew_ptr_last(&symbol->productions, prod,
			sizeof(t_production *)))
		return (1);
	va_start(ap, nb_symbols);
	prod->symbols = NULL;
	prod->from = symbol;
	prod->index = cfg->prod_index;
	i = 0;
	while (i < nb_symbols)
	{
		symbol_index = cfg->index_func((va_arg(ap, int)));
		if (ft_lstaddnew_ptr_last(&prod->symbols,
					&cfg->symbols[symbol_index], sizeof(t_symbol *)))
			return (1);
		i++;
	}
	cfg->prod_index++;
	va_end(ap);
	return (0);
}

void	init_grammar_from_initializer(t_cfg *cfg, t_cfg_initializer *cfgi)
{
	cfg->nb_symbols = cfgi->nb_symbols;
	cfg->nb_productions = cfgi->nb_productions;
	cfg->nb_terms = cfgi->nb_terms;
	cfg->nb_noterms = cfgi->nb_symbols - cfgi->nb_terms;
	cfg->grammar_holder = cfgi->grammar_holder;
	cfg->start_id = cfgi->start_id;
	cfg->epsilon_index = cfgi->epsilon_index;
	cfg->eoi_index = cfgi->eoi_index;
	cfg->index_func = cfgi->index_func;
	cfg->prod_index = 0;
	cfg->state_index = 0;
}

int		init_context_free_grammar(t_cfg *cfg, t_cfg_initializer *cfgi)
{
	init_grammar_from_initializer(cfg, cfgi);
	if (!(cfg->productions = (t_production *)malloc(sizeof(t_production)
					* (cfg->nb_productions))))
		return (1);
	if (!(cfg->symbols = (t_symbol *)malloc(sizeof(t_symbol)
					* cfg->nb_symbols)))
	{
		free(cfg->productions);
		return (1);
	}
	init_start_symbol(cfg, &cfg->start_symbol);
	return (init_context_free_grammar_symbols(cfg));
}
