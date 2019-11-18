/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:14:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:26:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_lr_automata(t_lr_parser *parser)
{
	t_state	*state;

	while ((state = ft_lstpop_ptr(&parser->states)))
		sh_free_state(state, &parser->cfg);
}

void	sh_free_production(void *p, size_t dummy)
{
	t_production *production;

	(void)dummy;
	production = (t_production *)p;
	ft_lstdel_ptr(&production->symbols);
}
