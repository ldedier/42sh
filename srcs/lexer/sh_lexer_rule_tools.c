/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:47:05 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/01 03:35:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_lexer_is_operator_char
**	Check if given char can be used as part of an operator.
**
**	returned Values:
**	 True or False
*/

int		sh_lexer_is_operator_char(int c)
{
	static const char	*chars = "|&;<>()-\0";
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

/*
** sh_lexer_check_operator:
**	Check if token formed by adding current char to current token
**	will form a valdi operator.
**	If yes, return True, and false else.
*/

int		sh_lexer_check_operator(t_lexer *lexer)
{
	int					i;
	static const char	*ops[] = {"<", ">", "&&", "||", "<&", ";;", "<<", ">>"
		"<&", ">&", "<<-", "(", ")", "!", NULL};

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
