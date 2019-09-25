/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:36:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/25 06:53:47 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		lexer_quoting_backslash(t_lexer *lexer)
{
	if (lexer->backslash)
		lexer->backslash = 0;
	else
	{
		lexer->backslash = 1;
		if (lexer->input[lexer->tok_start + lexer->tok_len + 1] == '\0'
			&& lexer->quoted != '\"')
		{
			ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
			return (LEX_OK);
		}
	}
	lexer->tok_len++;
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}

static int		lexer_quoting_start_quote(t_lexer *lexer)
{
	lexer->quoted = lexer->c;
	lexer->tok_len++;
	if (lexer->current_id == LEX_TOK_UNKNOWN)
		lexer->current_id = LEX_TOK_WORD;
	return (LEX_OK);
}

static int		lexer_quoting_simple_quote(t_lexer *lexer)
{
	if (lexer->c == '\'')
	{
		lexer->tok_len++;
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		lexer->quoted = 0;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}

static int		lexer_quoting_double_quote(t_lexer *lexer)
{
	if (lexer->c == '$' || lexer->c == '`' || lexer->c == '\\')
		return (LEX_CONTINUE);
	if (lexer->c == '"')
	{
		lexer->tok_len++;
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		lexer->quoted = 0;
	}
	else
		lexer->tok_len++;
	return (LEX_OK);
}

int				sh_lexer_rule4(t_lexer *lexer)
{
	if (lexer->quoted != '\'' && (lexer->c == '\\' || lexer->backslash))
		return (lexer_quoting_backslash(lexer));
	if (lexer->quoted == 0 && (lexer->c == '\'' || lexer->c == '"'))
		return (lexer_quoting_start_quote(lexer));
	if (lexer->quoted == '\'')
		return (lexer_quoting_simple_quote(lexer));
	else if (lexer->quoted == '"')
		return (lexer_quoting_double_quote(lexer));
	return (LEX_CONTINUE);
}
