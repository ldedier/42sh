/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_reserved_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 01:28:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 17:59:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_lexer_reserved_words(t_lexer *lexer, t_token *token)
{
	if (!token || !token->value)
		return (SUCCESS);
	if (lexer->first_word && token->id == LEX_TOK_WORD)
	{
		if (ft_strequ(token->value, "!"))
		{
			if (sh_verbose_lexer())
				ft_dprintf(2, RED"%s : Bang\n"EOC, token->value);
			t_token_update_id(LEX_TOK_BANG, token);
		}
		else if (ft_strrchr(token->value, '=') && sh_expansions_variable_valid_name(token->value))
		{
			if (sh_verbose_lexer())
				ft_dprintf(2, MAGENTA"%s : assignment word\n"EOC, token->value);
			t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
		}
		else if (ft_strequ(token->value, "{"))
			t_token_update_id(LEX_TOK_LBRACE, token);
		else if (ft_strequ(token->value, "}"))
			t_token_update_id(LEX_TOK_RBRACE, token);
		else
			lexer->first_word = lexer->first_word ? lexer->first_word - 1 : 0;
	}
	else if (token->id == LEX_TOK_SEMICOL
		|| token->id == LEX_TOK_PIPE
		|| token->id == LEX_TOK_AND_IF
		|| token->id == LEX_TOK_OR_IF
		|| token->id == LEX_TOK_OPN_PAR
		|| token->id == LEX_TOK_CLS_PAR)
		lexer->first_word = 1;
	else
		lexer->first_word = lexer->first_word ? lexer->first_word - 1 : 0;

	return (SUCCESS);
}
