/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:10:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 06:11:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_lexer_alias(t_lexer *lexer, char *value)
{
	char	*alias;

	if (!value || lexer->current_id != LEX_TOK_WORD || !lexer->first_word)
		return (LEX_CONTINUE);
	if (sh_vars_get_index(lexer->alias, value) == -1)
		return (LEX_CONTINUE);
	ft_dprintf(2, "alias detected : %s\n", value);
	ft_dprintf(2, "prev input : %s\n", lexer->input);
	alias = sh_vars_get_value(lexer->alias, NULL, value);
	lexer->input = ft_strrep_free(lexer->input, alias, lexer->tok_start, lexer->tok_len); // ret value
	t_lexer_reset(lexer, lexer->tok_start);
	ft_dprintf(2, "new input : %s\n", lexer->input);
	ft_dprintf(2, "tok_start : %d || tok_len : %d\n", lexer->tok_start, lexer->tok_len);
	ft_dprintf(2, "new lexer->c : %c\n", lexer->input[lexer->tok_start + lexer->tok_len]);
	return (LEX_OK);
}
