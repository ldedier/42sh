/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:47:05 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/10 14:47:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_is_operator(int op)
{
	if (op == LEX_TOK_AND_IF
	|| op == LEX_TOK_OR_IF
	|| op == LEX_TOK_DSEMI
	|| op == LEX_TOK_DLESS
	|| op == LEX_TOK_DGREAT
	|| op == LEX_TOK_LESSAND
	|| op == LEX_TOK_GREATAND
	|| op == LEX_TOK_LESSGREAT
	|| op == LEX_TOK_DLESSDASH
	|| op == LEX_TOK_CLOBBER
	|| op == LEX_TOK_PIPE
	|| op == LEX_TOK_AND
	|| op == LEX_TOK_SEMICOL
	|| op == LEX_TOK_LESS
	|| op == LEX_TOK_GREAT
	|| op == LEX_TOK_OPN_PAR
	|| op == LEX_TOK_CLS_PAR
	|| op == LEX_TOK_LBRACE
	|| op == LEX_TOK_RBRACE)
		return (1);
	return (0);
}
