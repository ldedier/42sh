/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_show.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:06:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/10 16:38:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	t_token_show_id_4(int i)
{
	if (i == LEX_TOK_AND_IF)
		ft_dprintf(2, "AND_IF");
	else if (i == LEX_TOK_QUOTE_BACK)
		ft_dprintf(2, "QUOTE_BACK");
	else if (i == LEX_TOK_IO_NUMBER)
		ft_dprintf(2, "IO_NUMBER");
	else if (i == LEX_TOK_RBRACE)
		ft_dprintf(2, "RBRACE");
	else if (i == LEX_TOK_LBRACE)
		ft_dprintf(2, "LBRACE");
	else if (i == LEX_TOK_BANG)
		ft_dprintf(2, "BANG");
	else
		ft_dprintf(2, COLOR_RED"Undefined Token (%d)"COLOR_END, i);
}

static void	t_token_show_id_3(int i)
{
	if (i == LEX_TOK_OR_IF)
		ft_dprintf(2, "OR_IF");
	else if (i == LEX_TOK_DSEMI)
		ft_dprintf(2, "DSEMI");
	else if (i == LEX_TOK_DLESS)
		ft_dprintf(2, "DLESS");
	else if (i == LEX_TOK_DGREAT)
		ft_dprintf(2, "DGREAT");
	else if (i == LEX_TOK_LESSAND)
		ft_dprintf(2, "LESSAND");
	else if (i == LEX_TOK_GREATAND)
		ft_dprintf(2, "GREATAND");
	else if (i == LEX_TOK_LESSGREAT)
		ft_dprintf(2, "LESSGREAT");
	else if (i == LEX_TOK_DLESSDASH)
		ft_dprintf(2, "DLESSDASH");
	else if (i == LEX_TOK_CLOBBER)
		ft_dprintf(2, "CLOBBER");
	else if (i == LEX_TOK_WORD)
		ft_dprintf(2, "%sWORD%s", BLUE, EOC);
	else if (i == LEX_TOK_TOKEN)
		ft_dprintf(2, "TOKEN");
	else
		t_token_show_id_4(i);
}

static void	t_token_show_id_2(int i)
{
	if (i == LEX_TOK_QUOTE_SPL)
		ft_dprintf(2, "QUOTE_SPL");
	else if (i == LEX_TOK_QUOTE_DBL)
		ft_dprintf(2, "QUOTE_DBL");
	else if (i == LEX_TOK_SPACE)
		ft_dprintf(2, "SPACE");
	else if (i == LEX_TOK_TAB)
		ft_dprintf(2, "");
	else if (i == LEX_TOK_NEWLINE)
		ft_dprintf(2, "NEWLINE");
	else if (i == LEX_TOK_STAR)
		ft_dprintf(2, "STAR");
	else if (i == LEX_TOK_QUEST)
		ft_dprintf(2, "QUEST");
	else if (i == LEX_TOK_HASH)
		ft_dprintf(2, "HASH");
	else if (i == LEX_TOK_TILD)
		ft_dprintf(2, "TILD");
	else if (i == LEX_TOK_EQUAL)
		ft_dprintf(2, "EQUAL");
	else if (i == LEX_TOK_PERCENT)
		ft_dprintf(2, "PERCENT");
	else
		t_token_show_id_3(i);
}

void		t_token_show(t_token *token)
{
	t_token_show_id(token->id);
	ft_dprintf(2, ":%s", token->value);
	if (token->expansion)
		ft_dprintf(2, " (expansion)");
}

void		t_token_show_id(int i)
{
	if (i == LEX_TOK_UNKNOWN)
		ft_dprintf(2, COLOR_RED"UNKNOWN"COLOR_END);
	else if (i == LEX_TOK_ASSIGNMENT_WORD)
		ft_dprintf(2, "%sASSIGMENT WORD%s", CYAN, EOC);
	else if (i == LEX_TOK_PIPE)
		ft_dprintf(2, "PIPE");
	else if (i == LEX_TOK_AND)
		ft_dprintf(2, "AND");
	else if (i == LEX_TOK_SEMICOL)
		ft_dprintf(2, "SEMICOL");
	else if (i == LEX_TOK_LESS)
		ft_dprintf(2, "LESS");
	else if (i == LEX_TOK_GREAT)
		ft_dprintf(2, "GREAT");
	else if (i == LEX_TOK_OPN_PAR)
		ft_dprintf(2, "OPN_PAR");
	else if (i == LEX_TOK_CLS_PAR)
		ft_dprintf(2, "CLS_PAR");
	else if (i == LEX_TOK_DOLLAR)
		ft_dprintf(2, "DOLLAR");
	else if (i == LEX_TOK_BACK_SLASH)
		ft_dprintf(2, "BACK_SLASH");
	else
		t_token_show_id_2(i);
}
