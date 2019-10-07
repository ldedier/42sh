/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:45:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/06 01:29:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule8(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_WORD)
	{
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
