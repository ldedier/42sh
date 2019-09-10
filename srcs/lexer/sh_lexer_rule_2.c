/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/10 16:40:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
