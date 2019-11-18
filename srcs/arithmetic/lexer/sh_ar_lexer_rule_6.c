/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/18 03:24:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_6(t_lexer *lexer)
{
	int		ret;

	if (lexer->quoted)
		return (LEX_CONTINUE);
	if (lexer->c == '\n' || lexer->c == ' ' || lexer->c == '\t')
	{
		ret = t_ar_lexer_add_token(lexer);
		lexer->tok_start += 1;
		return (ret);
	}
	return (LEX_CONTINUE);
}
