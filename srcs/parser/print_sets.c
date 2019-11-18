/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:06:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:06:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_process_print_set(t_cfg *cfg, char *sets)
{
	int i;
	int first;

	i = 0;
	first = 1;
	while (i < cfg->nb_terms)
	{
		if (sets[i])
		{
			if (!first)
				ft_printf(" ; ");
			sh_print_symbol(&cfg->symbols[i], cfg);
			first = 0;
		}
		i++;
	}
}

void	sh_print_first_set(t_cfg *cfg, t_symbol *symbol)
{
	ft_printf("first sets of ");
	sh_print_symbol(symbol, cfg);
	ft_printf(" :\n");
	sh_process_print_set(cfg, symbol->first_sets);
	ft_printf("\n\n");
}

void	sh_print_follow_set(t_cfg *cfg, t_symbol *symbol)
{
	ft_printf("follow sets of ");
	sh_print_symbol(symbol, cfg);
	ft_printf(" :\n");
	sh_process_print_set(cfg, symbol->follow_sets);
	ft_printf("\n\n");
}

void	print_follow_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = cfg->nb_terms;
	j = 0;
	ft_printf("%s%sFOLLOW SETS:\n\n%s", BOLD, UNDERLINE, EOC);
	while (j < cfg->nb_noterms)
	{
		sh_print_follow_set(cfg, &cfg->symbols[i++]);
		j++;
	}
}

void	print_first_sets(t_cfg *cfg)
{
	int i;
	int j;

	i = cfg->nb_terms;
	j = 0;
	ft_printf("%s%sFIRST SETS:\n\n%s", BOLD, UNDERLINE, EOC);
	while (j < cfg->nb_noterms)
	{
		sh_print_first_set(cfg, &cfg->symbols[i++]);
		j++;
	}
}
