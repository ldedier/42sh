/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:54:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/05/07 16:52:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_lexer_exp(t_lexer *lexer)
{
	sh_lexer_exp_recursive(lexer, &lexer->input, lexer->input);
	return (LEX_OK);
}

int			sh_lexer_exp_replace(t_expansion *expansion, char **input)
{
	*input = ft_strrep_free(*input, expansion->res->str, expansion->original, 1);
	if (!(*input))
		return (LEX_ERR);
	return (LEX_OK);
}

int		sh_lexer_exp_recursive(t_lexer *lexer, char **input, char *original)
{
	t_expansion	exp;

	if (sh_lexer_exp_init(original, &exp) == LEX_ERR)
		return (LEX_ERR);
	t_expansion_show(&exp);
	if (ft_strpbrk(exp.expansion, "~`$") && !ft_strstr(exp.expansion, "$$"))
	{
		if (sh_lexer_exp_recursive(lexer, input, exp.expansion) == LEX_ERR)
			return (LEX_ERR);
		t_expansion_free(&exp); //Updating (improve ??)
		if (sh_lexer_exp_init(original, &exp) == LEX_ERR)
			return (LEX_ERR);
	}
	exp.process(lexer, &exp);
	if (sh_lexer_exp_replace(&exp, input) == LEX_ERR)
		return (LEX_ERR);
	t_expansion_free(&exp); /// Leaks all function long
	return (LEX_OK);
}