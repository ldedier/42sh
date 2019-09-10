/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/10 16:18:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_lexer_is_operator:
**	Returnded Values
**		0 : Operator formed is valid
**		1 : Operator formed is invalid
**		2 : Invalid character given
*/

int		sh_lexer_is_operator_char(int c)
{
	static const char	*chars = "|&;<>(){}-\0";
	int					i;

	i = 0;
	if (c == '\0')
		return (0);
	while (chars[i])
	{
		if (chars[i] == c)
			break ;
		i++;
	}
	if (!chars[i])
		return (0);
	return (1);
}

int		sh_lexer_check_operator(t_lexer *lexer)
{
	static const char	*ops[] = {"<", ">", "&&", "||", "<&", ";;", "<<", ">>"
		"<&", ">&", "<<-", "{", "}", "(", ")", NULL};
		// "<>", ">|"};
	int					i;

	i = 0;
	lexer->tok_len++;
	while (ops[i])
	{
		if (ft_strnequ(ops[i], lexer->input + lexer->tok_start, lexer->tok_len))
		{
			lexer->tok_len--;
			return (1);
		}
		i++;
	}
	lexer->tok_len--;
	return (0);
}

int		sh_lexer_rule2(t_lexer *lexer)
{
	const int		offset[] = {1, 0xff00, 0xff0000};

	if (lexer->quoted > 0)
		return (LEX_CONTINUE);
	if (!sh_lexer_is_operator_char(lexer->current_id & 0x00ff))
		return (LEX_CONTINUE);
	if (sh_lexer_is_operator_char(lexer->c))
	{
		if (sh_lexer_check_operator(lexer))
		{
			lexer->current_id += offset[lexer->tok_len] * lexer->c;
			lexer->tok_len++;
			return (LEX_OK);
		}
		return (LEX_CONTINUE);
	}
	return (LEX_CONTINUE);
}
