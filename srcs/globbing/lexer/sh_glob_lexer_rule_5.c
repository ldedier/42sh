/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_lexer_rule_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:46:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 11:16:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_glob_lexer_rule_5(t_glob_lexer *lexer)
{
	int		ret;
	t_list	**regexp_list;

	if (!lexer->quoted && (lexer->c == '*' || lexer->c == '?'))
	{
		regexp_list =
			&((t_list**)lexer->regexp_tab->tbl)[lexer->regexp_tab_index];
		if (t_glob_lexer_add_str(lexer))
			return (LEX_FAIL);
		if (lexer->c == '*')
			ret = sh_regexp_parse_new_star(&lexer->tok_start, regexp_list);
		else
			ret = sh_regexp_parse_new_quest(&lexer->tok_start, regexp_list);
		return (ret);
	}
	return (LEX_CONTINUE);
}
