/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ar_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:12:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 21:10:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	t_ar_token_show_1(t_token *token)
{
	if (token->id == (t_symbol_id)LEX_TOK_AR_GREATEQ)
		ft_dprintf(2, ">=");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_EQUAL)
		ft_dprintf(2, "==");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_NOT_EQUAL)
		ft_dprintf(2, "!=");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_INTEGER)
		ft_dprintf(2, "INT : %ld", token->lval);
	else if (token->id == (t_symbol_id)LEX_TOK_AR_VARIABLE)
		ft_dprintf(2, "VAR : %s", token->value);
	else if (token->id == (t_symbol_id)LEX_TOK_AR_INC)
		ft_dprintf(2, "++");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_DEC)
		ft_dprintf(2, "--");
	else if (token->id == (t_symbol_id)END_OF_INPUT_AR)
		ft_dprintf(2, "EOI");
}

void	t_ar_token_show(t_token *token)
{
	if (token->id == (t_symbol_id)LEX_TOK_AR_AND)
		ft_dprintf(2, "&&");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_OR)
		ft_dprintf(2, "||");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_PLUS)
		ft_dprintf(2, "+");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_MINUS)
		ft_dprintf(2, "-");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_MULTIPLY)
		ft_dprintf(2, "*");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_DIVIDE)
		ft_dprintf(2, "/");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_MODULO)
		ft_dprintf(2, "%%");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_LESS)
		ft_dprintf(2, "<");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_GREAT)
		ft_dprintf(2, ">");
	else if (token->id == (t_symbol_id)LEX_TOK_AR_LESSEQ)
		ft_dprintf(2, "<=");
	else
		t_ar_token_show_1(token);
}

void	t_ar_token_free(t_token *token)
{
	if (token->value)
		ft_strdel(&token->value);
	free(token);
}
