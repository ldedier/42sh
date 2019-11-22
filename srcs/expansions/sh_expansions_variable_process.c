/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_variable_process.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:27:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/21 14:03:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_expansions_variable_process_hash(
	t_context *context, t_expansion *exp)
{
	char	*value;

	value = sh_vars_get_value(context->env, context->vars, exp->expansion + 1);
	if (!value)
		exp->res = ft_dy_str_new_str("0");
	else
	{
		value = ft_itoa(ft_strlen(value));
		exp->res = ft_dy_str_new_ptr(
			value, ft_strlen(value), ft_strlen(value) + 1);
	}
	if (!(exp->res))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_variable (3)"));
	return (SUCCESS);
}

/*
** sh_expansions_variable_process:
**	Function called to fill the expansion's res field using informations given
**	in the t_expansion structure.
**	This function is after expansion detection and before field splitting
**	They are two main cases :
**		if first char is a '#' result is lenght of the parameter
**		else result is value of this parameter
**
**	return Value:
**		FAILURE : malloc error
**		SUCCESS : Successfullly filled exp->res
*/

int			sh_expansions_variable_process(
	t_context *context, t_expansion *exp)
{
	char	*value;

	if (!exp->expansion)
	{
		if (!(exp->res = ft_dy_str_new_str(exp->original)))
		{
			return (sh_perror(
				SH_ERR1_MALLOC, "sh_expansions_variable_process (1)"));
		}
		return (SUCCESS);
	}
	if (*exp->expansion == '#')
		return (sh_expansions_variable_process_hash(context, exp));
	value = sh_vars_get_value(context->env, context->vars, exp->expansion);
	if (!value)
		exp->res = ft_dy_str_new_str("");
	else
		exp->res = ft_dy_str_new_str(value);
	if (!(exp->res))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_variable (2)"));
	return (SUCCESS);
}
