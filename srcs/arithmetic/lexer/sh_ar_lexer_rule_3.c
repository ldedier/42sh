/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/18 06:07:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

// change name
int			rule_3_is_valid_op_first_char(char c)
{
	if (c == '&'
	|| c == '|'
	|| c == '+'
	|| c == '-'
	|| c == '*'
	|| c == '/'
	|| c == '%'
	|| c == '<'
	|| c == '>'
	|| c == '!'
	|| c == '=')
		return (1);
	return (0);
}
static void	rule3_set_token_id_two_len(t_lexer *lexer, char *value)
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

static void	rule3_set_token_id_one_len(t_lexer *lexer, char *value)
{
	if (value[0] == '+')
		lexer->current_id = LEX_TOK_AR_PLUS;
	else if (value[0] == '-')
		lexer->current_id = LEX_TOK_AR_MINUS;
	else if (value[0] == '*')
		lexer->current_id = LEX_TOK_AR_MULTIPLY;
	else if (value[0] == '/')
		lexer->current_id = LEX_TOK_AR_DIVIDE;
	else if (value[0] == '%')
		lexer->current_id = LEX_TOK_AR_MODULO;
	else if (value[0] == '<')
		lexer->current_id = LEX_TOK_AR_LESS;
	else if (value[0] == '>')
		lexer->current_id = LEX_TOK_AR_GREAT;
}

int		sh_ar_lexer_rule_3(t_lexer *lexer)
{
	if (lexer->tok_len == 0 || lexer->tok_len > 2)
		return (LEX_CONTINUE);
	if (rule_3_is_valid_op_first_char(lexer->input[lexer->tok_start]))
	{
		if (lexer->tok_len == 1)
			rule3_set_token_id_one_len(lexer, lexer->input + lexer->tok_start);
		else
			rule3_set_token_id_two_len(lexer, lexer->input + lexer->tok_start);
		return (t_ar_lexer_add_token(lexer));
	}
	return (LEX_CONTINUE);
}
