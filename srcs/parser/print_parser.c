/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:12:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 11:12:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_symbol_list(t_list *symbols, t_cfg *cfg)
{
	t_list		*ptr;
	int			start;
	t_symbol	*symbol;

	start = 1;
	ptr = symbols;
	while (ptr != NULL)
	{
		symbol = (t_symbol *)(ptr->content);
		if (!start)
			ft_printf(" ");
		sh_print_symbol(symbol, cfg);
		ptr = ptr->next;
		start = 0;
	}
}

void	sh_print_automata(t_lr_parser *parser, int depth)
{
	t_list	*ptr;
	t_state	*state;

	ft_printf("%s%sAUTOMATA STATES:\n\n%s", BOLD, UNDERLINE, EOC);
	ptr = parser->states;
	while (ptr != NULL)
	{
		state = (t_state *)ptr->content;
		sh_print_state(state, depth, &parser->cfg);
		ft_printf("/////////////////////////////////\n");
		ptr = ptr->next;
	}
}

void	sh_print_cfg(t_cfg *cfg)
{
	print_non_terminals_productions(cfg);
	print_first_sets(cfg);
	print_follow_sets(cfg);
}

void	sh_print_parser(t_lr_parser *parser, int depth)
{
	sh_print_cfg(&parser->cfg);
	sh_print_automata(parser, depth);
	sh_print_lr_table(parser);
}
