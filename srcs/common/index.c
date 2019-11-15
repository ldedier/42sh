/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:49:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 11:31:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_index_4(t_symbol_id id)
{
	if (id == LEX_TOK_DLESSDASH)
		return (33);
	else if (id == LEX_TOK_CLOBBER)
		return (34);
	else if (id >= LEX_TOK_IF && id <= LEX_TOK_IN)
		return (id - LEX_TOK_IF + 35);
	else if (id < LEX_TOK_IF)
		return (id - LEX_TOK_TOKEN + 48);
	else
		return (-1);
}

int		sh_index_3(t_symbol_id id)
{
	if (id == LEX_TOK_TILD)
		return (22);
	else if (id == LEX_TOK_EQUAL)
		return (23);
	else if (id == LEX_TOK_PERCENT)
		return (24);
	else if (id == LEX_TOK_AND_IF)
		return (25);
	else if (id == LEX_TOK_OR_IF)
		return (26);
	else if (id == LEX_TOK_DSEMI)
		return (27);
	else if (id == LEX_TOK_DLESS)
		return (28);
	else if (id == LEX_TOK_DGREAT)
		return (29);
	else if (id == LEX_TOK_LESSAND)
		return (30);
	else if (id == LEX_TOK_GREATAND)
		return (31);
	else if (id == LEX_TOK_LESSGREAT)
		return (32);
	else
		return (sh_index_4(id));
}

int		sh_index_2(t_symbol_id id)
{
	if (id == LEX_TOK_DOLLAR)
		return (11);
	else if (id == LEX_TOK_BACK_SLASH)
		return (12);
	else if (id == LEX_TOK_QUOTE_BACK)
		return (13);
	else if (id == LEX_TOK_QUOTE_SPL)
		return (14);
	else if (id == LEX_TOK_QUOTE_DBL)
		return (15);
	else if (id == LEX_TOK_SPACE)
		return (16);
	else if (id == LEX_TOK_TAB)
		return (17);
	else if (id == LEX_TOK_NEWLINE)
		return (18);
	else if (id == LEX_TOK_STAR)
		return (19);
	else if (id == LEX_TOK_QUEST)
		return (20);
	else if (id == LEX_TOK_HASH)
		return (21);
	else
		return (sh_index_3(id));
}

int		sh_index(int id)
{
	if (id == LEX_TOK_UNKNOWN)
		return (0);
	else if (id == LEX_TOK_PIPE)
		return (1);
	else if (id == LEX_TOK_AND)
		return (2);
	else if (id == LEX_TOK_SEMICOL)
		return (3);
	else if (id == LEX_TOK_LESS)
		return (4);
	else if (id == LEX_TOK_GREAT)
		return (5);
	else if (id == LEX_TOK_OPN_PAR)
		return (6);
	else if (id == LEX_TOK_CLS_PAR)
		return (7);
	else if (id == LEX_TOK_LBRACE)
		return (8);
	else if (id == LEX_TOK_RBRACE)
		return (9);
	else if (id == LEX_TOK_BANG)
		return (10);
	else
		return (sh_index_2(id));
}
