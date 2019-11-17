/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 21:38:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_lexer_rule_2(t_lexer *lexer)
{
	char	prev_char;
	int		prev_len;

	if (lexer->quoted > 0)
		return (LEX_CONTINUE);
	if (lexer->tok_len  != 1)
		return (LEX_CONTINUE);
	prev_char = lexer->input[lexer->tok_start + lexer->tok_len];
	prev_len = lexer->tok_len;
	if ((prev_char == '<' || prev_char == '>') && lexer->c == '=')
		lexer->tok_len += 1;
	else if ((prev_char == '=' || prev_char == '!') && lexer->c == '=')
		lexer->tok_len += 1;
	else if ((prev_char == '&' || prev_char == '|')  && lexer->c == prev_char)
		lexer->tok_len += 1;
	else if ((prev_char == '+' || prev_char == '-') && lexer->c == prev_char)
		lexer->tok_len += 1;
	if (prev_len != lexer->tok_len)
		return (LEX_OK);
	return (LEX_CONTINUE);
}
