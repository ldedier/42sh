/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:04:06 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 03:26:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_print_symbol(t_symbol *symbol, t_cfg *cfg)
{
	if (sh_is_term(symbol, cfg))
		ft_dprintf(2, "%s%s%s", BLUE, symbol->debug, EOC);
	else
		ft_dprintf(2, "%s%s%s", RED, symbol->debug, EOC);
}

void	sh_print_token(t_token *token, t_cfg *cfg)
{
	if (cfg == g_glob.cfg)
	{
		if (token->id == LEX_TOK_WORD)
			ft_dprintf(2, "%s%s %s", YELLOW, token->value, EOC);
		else if (token->id == LEX_TOK_IO_NUMBER)
			ft_dprintf(2, "IO_NUMBER: %s%s %s ", YELLOW, token->value, EOC);
		else
			ft_dprintf(2, "%s%s %s", YELLOW, cfg->symbols[token->index].debug,
				EOC);
	}
	else
	{
		if (token->index == LEX_TOK_AR_INTEGER)
			ft_dprintf(2, "%s%d %s", YELLOW, token->lval, EOC);
		else if (token->index == LEX_TOK_AR_VARIABLE)
			ft_dprintf(2, "%s%s %s ", YELLOW, token->value, EOC);
		else
			ft_dprintf(2, "%s%s %s", YELLOW, cfg->symbols[token->index].debug,
				EOC);
	}
}

void	sh_print_token_list(t_list *list, t_cfg *cfg)
{
	t_list *ptr;

	ptr = list;
	ft_dprintf(2, "token list: ");
	while (ptr != NULL)
	{
		sh_print_token(ptr->content, cfg);
		ptr = ptr->next;
	}
	ft_dprintf(2, "\n\n");
}
