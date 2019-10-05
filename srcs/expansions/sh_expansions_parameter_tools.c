/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_parameter_tools.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:35:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 04:34:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_expansions_parameter_fill_format:
**	Write the expansion format in a static buffer using the head string.
*/

static void	sh_expansions_parameter_fill_format(char *head, char *format, int n)
{
	format[n] = 0;
	n--;
	while (n >= 0)
	{
		format[n] = head[n];
		n--;
	}
	return ;
}

/*
** sh_expansions_parameter_format:
**	read exp->expansion to find the foramt associated to the expansion.
**	It fill the format static string with the components.
**	The resulting format correspond to one of those :
**		[#] [:] -=?+ '\0'	or ##	or %%
**
**	Returned Values:
**		ERROR : wrong format detected
**		SUCCESS : format was successfully filled
*/

int			sh_expansions_parameter_format(t_expansion *exp, char *format, t_context *context)
{
	char	*head;
	int		i;

	head = exp->expansion;
	i = 0;
	if (*head == '#')
	{
		format[i] = '#';
		i++;
		head++;
	}
	if (!ft_isalpha(*head) && *head != '_')
	{
		if (!isatty(0))
		{
			sh_perror(exp->original, SH_BAD_SUBSTITUTE);
			sh_env_update_ret_value(context->shell, ERROR);
			return (STOP_CMD_LINE);
		}
		return (sh_perror_err(exp->original, SH_BAD_SUBSTITUTE));
	}
	head++;
	while (ft_isalnum((int)*head) || *head == '_')
		head++;
	if (ft_chpbrk(head[0], "-=?+") == 1)
		sh_expansions_parameter_fill_format(head, format + i, 1);
	else if (ft_chpbrk(head[0], ":") == 1 && ft_chpbrk(head[1], "-=?+") == 1)
		sh_expansions_parameter_fill_format(head, format + i, 2);
	else if (ft_strnstr(head, "##", 2) || ft_strnstr(head, "%%", 2))
		sh_expansions_parameter_fill_format(head, format + i, 2);
	else if (*head == '#' || *head == '%')
		sh_expansions_parameter_fill_format(head, format + i, 1);
	else
		return (sh_perror_err(exp->original, SH_BAD_SUBSTITUTE));
	return (SUCCESS);
}

/*
** sh_expansions_parameter_get_param :
**	read the t_expansion to get the param in an expresion of type ${param:+word}
**	then it's look for any assignment in environnment and then in vars.
**	The value of this assignment is returned, or null if no one were found.
**
**	Returned Values:
**		Value of var $param
**		NULL if no assignment was found
*/

char		*sh_expansions_parameter_get_param(
	t_context *context, t_expansion *exp)
{
	char	*value;
	char	*end;
	char	buf;

	if (!(end = ft_strpbrk(exp->expansion, ":-=?+%#")))
		end = exp->expansion + ft_strlen(exp->expansion);
	buf = *end;
	*end = 0;
	value = sh_vars_get_value(context->env, context->vars, exp->expansion);
	*end = buf;
	return (value);
}

/*
** sh_expansions_parameter_get_param :
**	read the t_expansion to get the word in an expresion of type ${param:+word}.
**
**	Returned Values:
**		Starting char of the null terminated string word.
*/
// Need to update comment

int		sh_expansions_parameter_get_word(
	t_context *context, t_expansion *exp, char *format, char **word)
{
	char		*start;
	t_dy_tab	*quotes;
	int			ret;

	start = ft_strstr(exp->expansion, format);
	if (exp->expansion[0] == '#')
		format++;
	start += ft_strlen(format);
	if (ft_strchr(start, '$') != ft_strrchr(start, '$'))
	{
		sh_perror(exp->original, SH_BAD_SUBSTITUTE);
		sh_env_update_ret_value(context->shell, ERROR);
		return (STOP_CMD_LINE);
	}
	if (!(*word = ft_strdup(start)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_parameter_get_word"));
	if (!(quotes = ft_dy_tab_new(5)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions"));
	ret = 0;
	ret = sh_expansions_tilde(word, context, quotes, &ret);
	if (!ret)
		ret = sh_expansions_scan(word, 0, context, quotes);
	if (!ret)
		sh_expansions_quote_removal((t_quote**)quotes->tbl);
	if (sh_verbose_expansion())
		ft_dprintf(2, BLUE"word after expansions : %s\n"EOC, *word);
	ft_dy_tab_del_ptr(quotes);
	return (ret);
}
