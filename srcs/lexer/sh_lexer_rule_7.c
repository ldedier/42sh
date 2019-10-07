/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:56 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 05:19:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule7(t_lexer *lexer)
{
	if (lexer->quoted > 0)
		return (LEX_CONTINUE);
	if (ft_iswhite(lexer->c))
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN && lexer->tok_len == 0)
		{
			lexer->tok_start++;
			return (LEX_OK);
		}
		if (t_lexer_add_token(lexer))
			return (LEX_FAIL);
		lexer->tok_start++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
