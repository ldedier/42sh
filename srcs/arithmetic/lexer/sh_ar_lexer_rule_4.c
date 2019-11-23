/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 13:39:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_ar_lexer_rule_4(t_lexer *lexer)
{
	if (lexer->c != '\'' && lexer->c != '"' && lexer->c != '\\')
		return (LEX_CONTINUE);
	ft_strdelchar(lexer->input, lexer->tok_start + lexer->tok_len);
	if (lexer->c == '\\')
		lexer->tok_len += 1;
	return (LEX_OK);
}
