/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_reserved_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 01:28:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 15:58:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	close_brace(t_lexer *lexer, t_token *token)
{
	if (ft_strequ(token->value, "}"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Rbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_RBRACE, token, g_glob.cfg);
		if (lexer->brace && lexer->brace->id== LEX_TOK_RBRACE)
			t_token_update_id(LEX_TOK_WORD, lexer->brace, g_glob.cfg);
		lexer->brace = token;
	}
}

static int		is_reserved(t_lexer *lexer, t_token *token)
{
	if (ft_strequ(token->value, "!"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Bang\n"EOC, token->value);
		t_token_update_id(LEX_TOK_BANG, token, g_glob.cfg);
		return (1);
	}
	else if (ft_strequ(token->value, "{"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Lbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_LBRACE, token, g_glob.cfg);
		lexer->brace = token;
		return (1);
	}
	return (0);
}

int				sh_lexer_reserved_words(t_lexer *lexer, t_token *token)
{
	if (!token || !token->value || token->id != LEX_TOK_WORD)
		return (SUCCESS);
	if (lexer->first_word)
	{
		if (is_reserved(lexer, token))
			;
		else if (ft_strrchr(token->value, '=') && sh_expansions_variable_valid_name(token->value))
		{
			if (sh_verbose_lexer())
				ft_dprintf(2, MAGENTA"%s : assignment word\n"EOC, token->value);
			t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token, g_glob.cfg);
		}
		else
			lexer->first_word = lexer->first_word >= 0 ? lexer->first_word - 1 : 0;
	}
	else if (lexer->brace)
		close_brace(lexer, token);
	return (SUCCESS);
}
