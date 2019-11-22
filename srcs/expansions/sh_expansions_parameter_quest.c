/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_equal.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 09:05:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 09:05:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_parameter_quest_msg
**		function used to create correct error message in ? and :?
**		parameter expansion
**
**	return Value:
**		ERROR
*/

static int	sh_expansions_parameter_quest_msg(
	char *format, t_context *context, t_expansion *exp)
{
	char	*buf;
	char	*word;
	int		ret;

	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	buf = ft_strpbrk(exp->expansion, ":?");
	*buf = 0;
	if (word && *word)
		sh_perror(exp->expansion, word);
	else
	{
		if (ft_strchr(format, ':'))
			sh_perror(exp->expansion,
			"parameter null or not set");
		else
			sh_perror(exp->expansion, "parameter not set");
	}
	if (!isatty(0))
		context->shell->running = 0;
	sh_env_update_ret_value(context->shell, ERROR);
	free(word);
	return (ERROR);
}

/*
** sh_expansions_parameter_quest:
**					parameter Not Null		parameter Null		parameter Unset
**parameter:?word	substitute parameter	error, exit			error, exit
**parameter?word	substitute parameter	substitute null		error, exit
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		ERROR : One of the previous condition happend
**		FAILURE : malloc error, one of previous condition happend
*/

int			sh_expansions_parameter_quest(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;

	param = sh_expansions_parameter_get_param(context, exp);
	if (!param)
		return (sh_expansions_parameter_quest_msg(format, context, exp));
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			return (sh_expansions_parameter_quest_msg(format, context, exp));
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (FAILURE);
	return (SUCCESS);
}
