/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 00:03:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_lexer_rule_3(t_lexer *lexer)
{
	if (lexer->tok_len == 0 || lexer->tok_len > 2)
		return (LEX_CONTINUE);
	if ((lexer->current_id >= LEX_TOK_AR_AND
			&& lexer->current_id <= LEX_TOK_AR_NOT_EQUAL)
		|| (lexer->current_id >= LEX_TOK_AR_INC
			&& lexer->current_id <= LEX_TOK_AR_DEC))
	{
		lexer->first_word = 0;
		return (t_ar_lexer_add_token(lexer));
	}
	return (LEX_CONTINUE);
}
