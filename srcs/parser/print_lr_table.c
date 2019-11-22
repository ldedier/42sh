/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lr_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:08:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:09:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_process_print_lr_table(t_lr_parser *parser, int i)
{
	int j;

	j = 0;
	while (j < parser->cfg.nb_symbols)
	{
		if (parser->lr_tables[i][j].action_enum == E_ACTION_ERROR)
		{
			ft_printf("%s\tERROR%s", RED, EOC);
		}
		else if (parser->lr_tables[i][j].action_enum == E_ACTION_REDUCE)
		{
			ft_printf("\tR%d",
					parser->lr_tables[i][j].action_union.production->index);
		}
		else if (parser->lr_tables[i][j].action_enum == E_ACTION_ACCEPT)
		{
			ft_printf("\tACCEPT");
		}
		else if (parser->lr_tables[i][j].action_enum == E_ACTION_SHIFT)
		{
			ft_printf("\tS%d",
					parser->lr_tables[i][j].action_union.state->index);
		}
		j++;
	}
}

void		sh_print_lr_table(t_lr_parser *parser)
{
	int i;
	int height;

	height = ft_lstlen(parser->states);
	i = 0;
	while (i < parser->cfg.nb_symbols)
	{
		ft_printf("\t");
		sh_print_symbol(&parser->cfg.symbols[i], &parser->cfg);
		i++;
	}
	ft_printf("\n");
	i = 0;
	while (i < height)
	{
		ft_printf("%#d", i);
		sh_process_print_lr_table(parser, i);
		ft_printf("\n");
		i++;
	}
}
