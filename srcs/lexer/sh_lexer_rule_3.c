/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:33:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/10 16:18:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_rule3(t_lexer *lexer)
{
	if (!lexer->current_id)
		return (LEX_CONTINUE);
	if (!sh_lexer_is_operator_char(lexer->current_id & 0x00ff))
		return (LEX_CONTINUE);
	ft_dprintf(2, "rule 3 : returned ");
	if (!sh_lexer_check_operator(lexer))
	{
		if (sh_lexer_is_operator(lexer->current_id))
		{
			ft_dprintf(2, "OK\n");
			t_lexer_add_token(lexer);
			lexer->tok_len = 0;
			return (LEX_OK);
		}
		ft_dprintf(2, "ERR\n");
		return (LEX_ERR);
	}
	ft_dprintf(2, "CONTINUE\n");
	return (LEX_CONTINUE);
}
