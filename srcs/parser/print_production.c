/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_production.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:05:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:05:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_production(t_production *production, t_cfg *cfg)
{
	sh_print_symbol(production->from, cfg);
	ft_printf(" → ");
	sh_print_symbol_list(production->symbols, cfg);
	ft_printf("\t(%d)", production->index);
}

void	print_non_terminal_production(t_symbol *symbol, t_cfg *cfg)
{
	t_list			*ptr;
	t_production	*production;

	ptr = symbol->productions;
	while (ptr != NULL)
	{
		production = (t_production *)ptr->content;
		ft_printf("\t");
		sh_print_production(production, cfg);
		ft_printf("\n");
		ptr = ptr->next;
	}
}

void	print_non_terminals_productions(t_cfg *cfg)
{
	int i;
	int j;

	i = cfg->nb_terms;
	j = 0;
	ft_printf("%s%sPRODUCTIONS:\n\n%s", BOLD, UNDERLINE, EOC);
	while (j < cfg->nb_noterms)
	{
		sh_print_symbol(&(cfg->symbols[i]), cfg);
		ft_printf(" : \n");
		print_non_terminal_production(&cfg->symbols[i++], cfg);
		j++;
	}
	ft_printf("\n");
}
