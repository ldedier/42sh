/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:10:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/09 02:29:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_lexer_alias(t_lexer *lexer, char *value)
{
	char	*alias;

	if (lexer->tok_len == 0 || lexer->current_id != LEX_TOK_WORD || !lexer->first_word)
		return (LEX_OK);
	if (sh_vars_get_index(lexer->alias, value) == -1)
		return (LEX_OK);
	alias = sh_vars_get_value(lexer->alias, NULL, value);
	if (sh_verbose_lexer())
		ft_dprintf(2, GREEN"\talias detected : (%s) => (%s)\n"EOC, value, alias);
	lexer->input = ft_strrep_free(lexer->input, alias, lexer->tok_start, lexer->tok_len);
	if (!lexer->input)
		return (LEX_FAIL);
	if (sh_verbose_lexer())
		ft_dprintf(2, GREEN"\trestarting detection on new input : %s\n"EOC, lexer->input + lexer->tok_start);
	t_lexer_reset(lexer, lexer->tok_start);
	return (LEX_CONTINUE);
}
