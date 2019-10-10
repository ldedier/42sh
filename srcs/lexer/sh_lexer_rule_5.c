/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:37:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/10 05:53:22 by jmartel          ###   ########.fr       */
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
	else
		end = -1;
	if (end <= 0)
		return (LEX_CONTINUE);
	lexer->tok_len += end;
	return (LEX_OK);
}

int				sh_lexer_rule5(t_lexer *lexer)
{
	if (lexer->quoted == '\'' || lexer->quoted == '\\')
		return (LEX_CONTINUE);
	if (lexer->c == '$' || lexer->c == '`')
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		return (sh_lexer_exp(lexer));
	}
	return (LEX_CONTINUE);
}
