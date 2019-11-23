/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_8.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 21:37:28 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_8(t_lexer *lexer)
{
	if (ft_isdigit(lexer->c))
	{
		lexer->current_id = LEX_TOK_AR_INTEGER;
		lexer->tok_len += 1;
		return (LEX_OK);
	}
	else if (ft_isalpha(lexer->c) || lexer->c == '_')
	{
		lexer->current_id = LEX_TOK_AR_VARIABLE;
		lexer->tok_len += 1;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
