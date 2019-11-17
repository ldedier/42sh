/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 21:42:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_1(t_lexer *lexer)
{
	int		ret;

	if (lexer->c == '\0')
	{
		if (lexer->quoted != 0)
			;; // shall return an error ?? (quoting may be handled in sh_lexer)
		ret = t_ar_lexer_add_token(lexer);
		if (ret == LEX_OK)
			return (LEX_END);
		return (ret);
	}
	return (LEX_CONTINUE);
}
