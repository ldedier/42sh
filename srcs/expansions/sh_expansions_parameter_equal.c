/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_equal.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 09:05:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 23:03:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	assign_word(
	t_context *context, t_expansion *exp, char *format, char *param)
{
	char	buff;
	char	*word;
	int		ret;

	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	param = ft_strstr(exp->expansion, format);
	buff = *param;
	*param = 0;
	if (sh_vars_assign_key_val(
		context->env, context->vars, exp->expansion, word))
	{
		free(word);
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_equal"));
	}
	*param = buff;
	exp->res = ft_dy_str_new_str(word);
	free(word);
	return (SUCCESS);
}

/*
** sh_expansions_parameter_equal
**					parameter Not Null		parameter Null		parameter Unset
**parameter:=word	substitute parameter	assign word			assign word
**parameter=word	substitute parameter	substitute null		assign word
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_equal(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	if (!param || (!(*param) && ft_strchr(format, ':')))
	{
		if ((ret = assign_word(context, exp, format, param)))
			return (ret);
	}
	else if (!*param)
		exp->res = ft_dy_str_new_str("");
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_equal"));
	return (SUCCESS);
}
