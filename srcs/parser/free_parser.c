/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:19:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/22 11:30:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_cfg(t_cfg *cfg)
{
	int i;

	i = 0;
	while (i < NB_SYMBOLS)
	{
		ft_lstdel(&cfg->symbols[i].productions, sh_free_production);
		i++;
	}
	ft_lstdel(&cfg->start_symbol.productions, sh_free_production);
}

void	sh_free_parser(t_lr_parser *parser)
{
	int i;

	sh_free_lr_automata(parser);
	ft_hash_table_del_ptr(parser->states_by_items);
	if (parser->lr_tables && parser->nb_states != -1)
	{
		i = 0;
		while (i < parser->nb_states)
		{
			free(parser->lr_tables[i]);
			i++;
		}
		free(parser->lr_tables);
	}
	sh_free_cfg(&parser->cfg);
}
