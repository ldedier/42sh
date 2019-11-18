/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/18 03:13:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_ar_lexer_rule_5(t_lexer *lexer)
{
	int		ret;

	if (rule_3_is_valid_op_first_char(lexer->c))
	{
		ret = t_lexer_add_token(lexer);
		lexer->tok_len += 1;
		return (ret);
	}
	return (LEX_CONTINUE);
}
