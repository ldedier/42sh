/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:33:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/10 01:42:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_lexer_is_operator:
**	If operator sent, as an int, is a valid, complete, operato return True.
**	Else it return False.
*/

static int	sh_lexer_is_operator(int op, t_lexer *lexer)
{
	if (op == LEX_TOK_AND_IF
	|| op == LEX_TOK_OR_IF
	|| op == LEX_TOK_SEMICOL
	|| op == LEX_TOK_AND
	|| op == LEX_TOK_OPN_PAR
	|| op == LEX_TOK_CLS_PAR)
	{
		lexer->first_word = 1;
		return (1);
	}
	else if (op == LEX_TOK_DSEMI
	|| op == LEX_TOK_DLESS
	|| op == LEX_TOK_DGREAT
	|| op == LEX_TOK_LESSAND
	|| op == LEX_TOK_GREATAND
	|| op == LEX_TOK_LESSGREAT
	|| op == LEX_TOK_DLESSDASH
	|| op == LEX_TOK_CLOBBER
	|| op == LEX_TOK_PIPE
	|| op == LEX_TOK_LESS
	|| op == LEX_TOK_GREAT)
		return (1);
	return (0);
}

int			sh_lexer_rule3(t_lexer *lexer)
{
	int		ret;

	if (!lexer->current_id)
		return (LEX_CONTINUE);
	if (!sh_lexer_is_operator_char(lexer->current_id & 0x00ff))
		return (LEX_CONTINUE);
	if (!sh_lexer_check_operator(lexer))
	{
		if (sh_lexer_is_operator(lexer->current_id, lexer))
		{
			if ((ret = t_lexer_add_token(lexer)))
			{
				if (ret == LEX_CONTINUE)
					return (LEX_OK);
				return (ret);
			}
			lexer->tok_len = 0;
			return (LEX_OK);
		}
		return (LEX_ERR);
	}
	return (LEX_CONTINUE);
}
