/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_reserved_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 01:28:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 04:56:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_lexer_is_reserved(t_lexer *lexer, t_token *token)
{
	if (ft_strequ(token->value, "!"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Bang\n"EOC, token->value);
		t_token_update_id(LEX_TOK_BANG, token);
		return (1);
	}
	else if (ft_strequ(token->value, "{"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Lbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_LBRACE, token);
		lexer->brace = token;
		return (1);
	}
	else if (lexer->brace && ft_strequ(token->value, "}"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Rbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_RBRACE, token);
		if (lexer->brace && lexer->brace->id== LEX_TOK_RBRACE)
			t_token_update_id(LEX_TOK_WORD, lexer->brace);
		lexer->brace = token;
		return (1);
	}
	return (0);
}

int				sh_lexer_reserved_words(t_lexer *lexer, t_token *token)
{
	if (!token || !token->value)
		return (SUCCESS);
	if (lexer->first_word)
	{
		ft_dprintf(2, "reserved words : token value : %s\n", token->value);
		if (sh_lexer_is_reserved(lexer, token))
			;
		else if (ft_strrchr(token->value, '=') && sh_expansions_variable_valid_name(token->value))
		{
			if (sh_verbose_builtin())
				ft_dprintf(2, RED"%s : assignment word\n"EOC, token->value);
			t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
		}
		else
		{
			lexer->first_word = 0;		
			ft_dprintf(2, RED"first word setted to 0\n"EOC);
		}
	}
	return (SUCCESS);
}
