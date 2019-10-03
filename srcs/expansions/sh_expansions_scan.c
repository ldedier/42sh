/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:17:39 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/01 15:54:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	double_quote(
	char **input, int *index, t_context *context, t_dy_tab *quotes)
{
	int	ret;

	if (t_quote_add_new(quotes, *index, (*input) + *index))
		return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
	(*index) += 1;
	while ((*input)[*index] && (*input)[*index] != '\"')
	{
		if ((*input)[*index] == '$')
		{
			if ((ret = sh_expansions_process(
				input, *input + *index, context, index, quotes)) != SUCCESS)
				return (ret);
		}
		else if ((*input)[*index] == '\\' && ft_strchr("$`\"\\", (*input)[*index + 1]))
		{
			if (t_quote_add_new(quotes, *index, (*input) + *index))
				return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
			(*index) += 2;
		}
		else if ((*input)[*index] == '\\' && (*input)[*index + 1] == '\n')
			ft_strdelchars((*input) + *index, 0, 2);
		else
			*index += 1;
	}
	if (!(*input)[*index])
		return (ERROR);
	if (t_quote_add_new(quotes, *index, (*input) + *index))
		return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
	(*index) += 1;
	return (SUCCESS);
}

static int	unquoted_var(char **input, int *index, t_context *context, t_dy_tab *quotes)
{
	int	ret;

	if ((ret = sh_expansions_process(
		input, *input + *index, context, index, quotes)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(context->shell, ret))
			return (FAILURE);
		return (ret);
	}
	return (SUCCESS);
}

static int	simple_quote(char **input, int *index, t_dy_tab *quotes)
{
	if (t_quote_add_new(quotes, *index, (*input) + *index))
		return (sh_perror(SH_ERR1_MALLOC, "simple_quote"));
	(*index) += 1;
	while ((*input)[*index] && (*input)[*index] != '\'')
		*index += 1;
	if (t_quote_add_new(quotes, *index, (*input) + *index))
		return (sh_perror(SH_ERR1_MALLOC, "simple_quote"));
	(*index) += 1;
	return (SUCCESS);
}

/*
** sh_scan_expansions:
** Scan input, starting at index
** Remove quote, double quote and backslah.
** Replace variable with looking in context variables.
**
** Returned Values :
**	ERROR : Bad expansion format detected
**	FAILURE : Malloc Error
**	STOP_CMD_LINE : ${?} or ${:?} returned an error => stop current line
**	SUCCESS : Successfully processed and repalced expansion by it's result.
*/

int			sh_expansions_scan(char **input, int index,
	t_context *context, t_dy_tab *quotes)
{
	int		ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'')
		simple_quote(input, &index, quotes);
	else if ((*input)[index] == '"')
	{
		if ((ret = double_quote(
			input, &index, context, quotes)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '$')
	{
		if ((ret = unquoted_var(input, &index, context, quotes)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '\\' && (*input)[index + 1] == '\n')
		ft_strdelchars((*input) + index, 0, 2);
	else
	{
		if (t_quote_add_new(quotes, index, (*input) + index))
			return (sh_perror(SH_ERR1_MALLOC, "double_quote"));
		index += 2;
	}
	return (sh_expansions_scan(input, index, context, quotes));
}
