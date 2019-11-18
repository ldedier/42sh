/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cfg_symbols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:26:22 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:27:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		init_start_symbol(t_cfg *cfg, t_symbol *symbol)
{
	symbol->id = cfg->nb_symbols + 1;
	symbol->productions = NULL;
	sh_add_prod(symbol, cfg, 1, cfg->start_id);
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

int		init_context_free_grammar_symbols(t_cfg *cfg)
{
	int i;

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
