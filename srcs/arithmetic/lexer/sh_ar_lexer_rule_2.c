/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/19 08:04:16 by jmartel          ###   ########.fr       */
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
** For inc and dec cases : If !lexer->word, we cannot delimit these tokens
**	do by continuating rule3 will delimit this token, else, it continue normal
**	process, and rule 3 will delimit token in next cycle.
*/

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
		{
			if (lexer->first_word)
				lexer->tok_len += 1;
			else
				return (LEX_CONTINUE);
		}
		if (prev_len != lexer->tok_len)
		{
			rule2_set_token_id_two_len(lexer, lexer->input + lexer->tok_start);
			return (LEX_OK);
		}
	}
	return (LEX_CONTINUE);
}
