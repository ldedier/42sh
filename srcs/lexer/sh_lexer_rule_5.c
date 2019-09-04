/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:37:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/06 19:10:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_lexer_exp(t_lexer *lexer)
{
	char	*start;
	int		end;

	start = lexer->input + lexer->tok_start + lexer->tok_len;
	if (ft_strnstr(start, "${", 2))
		end = sh_expansions_parameter_detect(start) + 1;
	else if (start[0] == '$')
		end = sh_expansions_variable_detect(start);
	else if (start[0] == '~')
		end = sh_expansions_tilde_detect(start);
	else
		end = -1;
	if (end <= 0)
		return (LEX_CONTINUE);
	lexer->expansion = '$';
	lexer->tok_len += end;
	return (LEX_OK);
}

int				sh_lexer_rule5(t_lexer *lexer)
{
	if (lexer->quoted == '\'' || lexer->quoted == '\\')// lexer->quoted == '\"' ?
		return (LEX_CONTINUE);
	if (lexer->c == '$' || lexer->c == '`' || lexer->c == '~')
	{
		if (lexer->c == '~' && lexer->tok_len != 0)
			return (LEX_CONTINUE);
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		return (sh_lexer_exp(lexer));
	}
	return (LEX_CONTINUE);
}
