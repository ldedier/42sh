/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 13:40:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_1(t_lexer *lexer)
{
	int		ret;

	if (lexer->c == '\0')
	{
		if (lexer->quoted != 0)
			return (LEX_ERR);
		ret = t_ar_lexer_add_token(lexer);
		lexer->current_id = END_OF_INPUT_AR;
		if (!ret)
			ret = t_ar_lexer_add_token(lexer);
		if (ret == LEX_OK)
			return (LEX_END);
		return (ret);
	}
	return (LEX_CONTINUE);
}
