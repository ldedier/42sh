/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_process.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:41:00 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/08 06:03:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_parameter_minus
**					parameter Not Null		parameter Null		parameter Unset
**parameter:-word	substitute parameter	substitute word		substitute word
**parameter-word	substitute parameter	substitute null		substitute word
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_minus(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if (!param)
	{
		if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
			return (ret);
		exp->res = ft_dy_str_new_str(word);
	}
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
		{
			if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
				return (ret);
			exp->res = ft_dy_str_new_str(word);
		}
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s\n", param, word);
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_minus"));
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
	char	*word;
	char	buff;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if (!param || (!(*param) && ft_strchr(format, ':')))
	{
		if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
			return (ret);
		param = ft_strstr(exp->expansion, format);
		buff = *param;
		*param = 0;
		sh_vars_assign_key_val(
			context->env, context->vars, exp->expansion, word);
		*param = buff;
		exp->res = ft_dy_str_new_str(word);
	}
	else if (!*param)
		exp->res = ft_dy_str_new_str("");
	else
		exp->res = ft_dy_str_new_str(param);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s\n", param, word);
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_equal"));
	return (SUCCESS);
}

/*
** sh_expansions_parameter_quest_msg
**		function used to create correct error message in ? and :?
**		parameter expansion
**
**	return Value:
**		ERROR
*/

static int	sh_expansions_parameter_quest_msg(
	char *format, t_context *context, char *expansion, char *word)
{
	char	*buf;

	buf = ft_strpbrk(expansion, ":?");
	*buf = 0;
	if (word && *word)
		sh_perror(expansion, word);
	else
	{
		if (ft_strchr(format, ':'))
			sh_perror(expansion,
			"parameter null or not set");
		else
			sh_perror(expansion, "parameter not set");
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
	char	*word;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if (!param)
	{
		if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
			return (ret);
		return (sh_expansions_parameter_quest_msg(format,
			context, exp->expansion, word));
	}
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
		{
			if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
				return (ret);
			return (sh_expansions_parameter_quest_msg(format,
				context, exp->expansion, word));
		}
		else
			exp->res = ft_dy_str_new_str("");
	}
	else
		exp->res = ft_dy_str_new_str(param);
	if (!exp->res)
		return (FAILURE);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s\n", param, word);
	return (SUCCESS);
}

/*
** sh_expansions_parameter_plus:
**					parameter Not Null		parameter Null		parameter Unset
**parameter:+word	substitute word			substitute null		substitute null
**parameter+word	substitute word			substitute word		substitute null
**
**	return Value:
**		SUCCESS : exp->res sucessfully filled
**		FAILURE : malloc error
*/

int			sh_expansions_parameter_plus(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!*param)
	{
		if (ft_strchr(format, ':'))
			exp->res = ft_dy_str_new_str("");
		else
		{
			if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
				return (ret);
			exp->res = ft_dy_str_new_str(word);
		}
	}
	else
	{
		if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
			return (ret);
		exp->res = ft_dy_str_new_str(word);
	}
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s\n", param, word);
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_"));
	return (SUCCESS);
}

int			sh_expansions_parameter_hash(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	char	*end;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	word = NULL;
	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	
	t_list	*matches;
	if (word)
		sh_globbing_for_substring_removal(param, word, &matches);
	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!word || !*word)
		exp->res = ft_dy_str_new_str(param);
	else
	{
		end = ft_strnstr(param, word, ft_strlen(word));
		if (!end)
			exp->res = ft_dy_str_new_str(param);
		else
			exp->res = ft_dy_str_new_str(param + ft_strlen(word));
	}
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_hash"));
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s <> format : %s\n", param, word, format);
	return (SUCCESS);
}

int			sh_expansions_parameter_percent(
	t_context *context, t_expansion *exp, char *format)
{
	char	*param;
	char	*word;
	char	*end;
	char	save;
	int		ret;

	param = sh_expansions_parameter_get_param(context, exp);
	if ((ret = sh_expansions_parameter_get_word(context, exp, format, &word)))
		return (ret);
	if (sh_verbose_expansion())
		ft_dprintf(2, "param : %s <> word : %s\n", param, word);
	if (!param)
		exp->res = ft_dy_str_new_str("");
	else if (!word || !*word)
		exp->res = ft_dy_str_new_str(param);
	else
	{
		end = ft_strrnstr(param, word, ft_strlen(word));
		if (!end)
			exp->res = ft_dy_str_new_str(param);
		else
		{
			save = *end;
			*end = 0;
			exp->res = ft_dy_str_new_str(param);
			*end = save;
		}
	}
	if (word)
		ft_strdel(&word);
	if (!exp->res)
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_hash"));
	return (SUCCESS);
}
