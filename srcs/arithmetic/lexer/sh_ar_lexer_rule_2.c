/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/19 06:49:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	rule2_set_token_id_two_len(t_lexer *lexer, char *value)
{
	if (value[0] == '&')
		lexer->current_id = LEX_TOK_AR_AND;
	else if (value[0] == '|')
		lexer->current_id = LEX_TOK_AR_OR;
	else if (value[0] == '<')
		lexer->current_id = LEX_TOK_AR_LESSEQ;
	else if (value[0] == '>')
		lexer->current_id = LEX_TOK_AR_GREATEQ;
	else if (value[0] == '=')
		lexer->current_id = LEX_TOK_AR_EQUAL;
	else if (value[0] == '!')
		lexer->current_id = LEX_TOK_AR_NOT_EQUAL;
	else if (value[0] == '+')
		lexer->current_id = LEX_TOK_AR_INC;
	else if (value[0] == '-')
		lexer->current_id = LEX_TOK_AR_DEC;
}

/*
** Handle case of $((---)) => (-) (-) (-)
**	Idem with some '+'
**
** lexer->expansion is used to store if we are in a '+' or '-' serie.
*/

static int	handle_inc_and_dec(t_lexer *lexer)
{
	char	next_char;
	int		id;

	next_char = lexer->input[lexer->tok_start + lexer->tok_len + 1];
	if (next_char == lexer->c)
	{
		if (lexer->c == '-')
			id = LEX_TOK_AR_MINUS;
		else
			id = LEX_TOK_AR_PLUS;
		lexer->current_id = id;
		if (t_ar_lexer_add_token(lexer) != LEX_OK)
			return (LEX_FAIL);
		lexer->tok_len += 1;
		lexer->current_id = id;
		if (t_ar_lexer_add_token(lexer) != LEX_OK)
			return (LEX_FAIL);
		lexer->expansion = lexer->c;
		return (LEX_OK);
	}
	lexer->tok_len += 1;
	rule2_set_token_id_two_len(lexer, lexer->input + lexer->tok_start);
	return (LEX_OK);
}

int			sh_ar_lexer_rule_2(t_lexer *lexer)
{
	char	prev_char;
	int		prev_len;

	if (lexer->quoted > 0)
		return (LEX_CONTINUE);
	if (lexer->tok_len  != 1)
		return (LEX_CONTINUE);
	if (lexer->tok_start + lexer->tok_len)
	{
		prev_char = lexer->input[lexer->tok_start + lexer->tok_len - 1];
		prev_len = lexer->tok_len;
		if ((prev_char == '<' || prev_char == '>') && lexer->c == '=')
			lexer->tok_len += 1;
		else if ((prev_char == '=' || prev_char == '!') && lexer->c == '=')
			lexer->tok_len += 1;
		else if ((prev_char == '&' || prev_char == '|')  && lexer->c == prev_char)
			lexer->tok_len += 1;
		else if ((prev_char == '+' || prev_char == '-') && lexer->c == prev_char)
			return (handle_inc_and_dec(lexer));
		if (prev_len != lexer->tok_len)
		{
			rule2_set_token_id_two_len(lexer, lexer->input + lexer->tok_start);
			return (LEX_OK);
		}
	}
	return (LEX_CONTINUE);
}
