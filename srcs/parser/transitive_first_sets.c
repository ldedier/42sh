/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:46:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 07:01:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_process_transitive_first_set(t_symbol *symbol,
			int index, int *changes)
{
	if (symbol->first_sets[index] == 0)
	{
		symbol->first_sets[index] = 1;
		*changes = 1;
	}
}

/*
** don't make ε belong to first if start with ε cause
** it might have others stuff behind
*/

void	sh_process_transitive_first_sets(t_symbol *symbol,
			t_symbol *prod_symbol, int *changes, t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < cfg->nb_terms - 1)
	{
		if (prod_symbol->first_sets[i] == 1)
			sh_process_transitive_first_set(symbol, i, changes);
		i++;
	}
}

void	sh_process_transitive_first_set_2(char *first_sets, int index)
{
	if (first_sets[index] == 0)
		first_sets[index] = 1;
}

/*
** don't make ε belong to first if start with ε cause
** it might have others stuff behind
*/

void	sh_process_transitive_first_sets_2(char *first_sets,
			t_symbol *prod_symbol, t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < cfg->nb_terms - 1)
	{
		if (prod_symbol->first_sets[i] == 1)
			sh_process_transitive_first_set_2(first_sets, i);
		i++;
	}
}
