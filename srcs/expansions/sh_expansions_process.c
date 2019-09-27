/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:58:45 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/27 23:01:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_init:
**	Try to fill type, expansion, original and process fields of a t_expansion
**	structure for parameter and variable expansions.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

static int	sh_expansions_init(char *original, t_expansion *exp)
{
	ft_bzero(exp, sizeof(t_expansion));
	if (!original)
		return (ERROR);
	if (ft_strnstr(original, "${", 2))
		return (sh_expansions_parameter_fill(exp, original));
	else if (ft_strnstr(original, "$", 1))
		return (sh_expansions_variable_fill(exp, original));
	else
		return (ERROR);
}

/*
** sh_expansions_process:
**	For parameter and variables expansions detection.
**	Condition `if (ret && exp.res)` is here to handle case of a solo $.
**	This is linked to the function sh_expansions_variable_fill.
**
**	Return Value:
**		FAILURE : malloc error
**		ERROR : expansion is invalid
**		SUCCESS : successfully filled expansion
*/

int			sh_expansions_process(
	char **input, char *original, t_context *context, int *index, t_dy_tab *quotes)
{
	t_expansion	exp;
	int			ret;

	ret = sh_expansions_init(original, &exp);
	if (sh_verbose_expansion())
		t_expansion_show(&exp);
	if (!ret)
		ret = exp.process(context, &exp);
	if (!ret)
		ret = sh_expansions_replace(&exp, input, *index, (t_quote**)quotes->tbl);
	if (ret && exp.type == EXP_VAR)
	{
		(*index)++;
		t_expansion_free_content(&exp);
		return (SUCCESS);
	}
	if (ret)
	{
		t_expansion_free_content(&exp);
		return (ret);
	}
	*index += ft_strlen(exp.res->str);
	t_expansion_free_content(&exp);
	return (SUCCESS);
}
