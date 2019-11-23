/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_7.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 21:38:05 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_7(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_AR_INTEGER)
	{
		if (ft_isdigit(lexer->c))
		{
			lexer->tok_len += 1;
			return (LEX_OK);
		}
		return (t_ar_lexer_add_token(lexer));
	}
	else if (lexer->current_id == LEX_TOK_AR_VARIABLE)
	{
		if (ft_isalnum(lexer->c) || lexer->c == '_')
		{
			lexer->tok_len += 1;
			return (LEX_OK);
		}
		return (t_ar_lexer_add_token(lexer));
	}
	return (LEX_CONTINUE);
}
