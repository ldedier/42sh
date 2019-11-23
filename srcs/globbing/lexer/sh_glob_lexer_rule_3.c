/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_lexer_rule_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:46:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/23 17:54:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Delete current quote id exists in quotes tab, and update index of next cases.
*/

static void	treat_quotes(t_glob_lexer *lexer)
{
	int		i;
	t_quote	*quote;

	i = 0;
	while (lexer->quotes->tbl[i])
	{
		quote = ((t_quote**)lexer->quotes->tbl)[i];
		if (quote->index == lexer->tok_start + lexer->tok_len)
			break ;
		i++;
	}
	if (lexer->quotes->tbl[i])
	{
		ft_strdelchar(((t_quote**)lexer->quotes->tbl)[i]->c, 0);
		ft_dy_tab_suppr_index(lexer->quotes, i);
	}
	else
		lexer->tok_len += 1;
	while (lexer->quotes->tbl[i])
	{
		((t_quote**)lexer->quotes->tbl)[i]->index -= 1;
		((t_quote**)lexer->quotes->tbl)[i]->c -= 1;
		i++;
	}
}

int			sh_glob_lexer_rule_3(t_glob_lexer *lexer)
{
	if (lexer->c == '\'' || lexer->c == '\"')
	{
		lexer->quoted = lexer->quoted ? 0 : lexer->c;
		treat_quotes(lexer);
		return (LEX_OK);
	}
	else if (lexer->c == '\\')
	{
		treat_quotes(lexer);
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
