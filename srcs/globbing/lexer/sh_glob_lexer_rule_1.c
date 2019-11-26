/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_lexer_rule_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:46:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 08:27:47 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_glob_lexer_rule_1(t_glob_lexer *lexer)
{
	if (!lexer->c)
	{
		if (lexer->quoted)
			return (LEX_ERR);
		if (t_glob_lexer_add_str(lexer))
			return (LEX_FAIL);
		if (sh_verbose_globbing())
		{
			ft_dprintf(2, GREEN"\tparsed => ");
			t_regexp_show_list(lexer->regexp_tab->tbl[lexer->regexp_tab_index]);
		}
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}
