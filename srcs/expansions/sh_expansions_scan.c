/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:17:39 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/23 09:37:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	unquoted_var(
		char **input, int *index, t_context *context, t_dy_tab *quotes)
{
	int	ret;

	if ((ret = sh_expansions_process(input, context, index, quotes)))
	{
		sh_env_update_ret_value(context->shell, ret);
		return (ret);
	}
	return (SUCCESS);
}

static int	simple_quote(char **input, int *index, t_dy_tab *quotes)
{
	if (t_quote_add_new(quotes, *index, (*input) + *index, 1))
		return (sh_perror(SH_ERR1_MALLOC, "simple_quote"));
	(*index) += 1;
	while ((*input)[*index] && (*input)[*index] != '\'')
		*index += 1;
	if (t_quote_add_new(quotes, *index, (*input) + *index, 1))
		return (sh_perror(SH_ERR1_MALLOC, "simple_quote"));
	(*index) += 1;
	return (SUCCESS);
}

static int	sh_quote_original_input(
		char **input, int *index, t_dy_tab *quotes, int new_quote[2])
{
	if (new_quote[0] < new_quote[1]
			&& ft_strninsert_free(input, new_quote, '\'', 2) >= 0)
	{
		new_quote[1] += 1;
		if (t_quote_add_new(
					quotes, new_quote[0], (*input) + new_quote[0], 0) != SUCCESS
			|| t_quote_add_new(
				quotes, new_quote[1], (*input) + new_quote[1], 0) != SUCCESS)
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_scan"));
		*index += 2;
	}
	else if (new_quote[0] < new_quote[1])
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_scan"));
	return (SUCCESS);
}

static int	sh_manage_special_char(
		char **in, int *i, t_context *ctxt, t_dy_tab *quotes)
{
	int	ret;

	if ((*in)[*i] == '\'')
		simple_quote(in, i, quotes);
	else if ((*in)[*i] == '"')
	{
		if ((ret = sh_expansions_scan_double_quote(
						in, i, ctxt, quotes)) != SUCCESS)
			return (ret);
	}
	else if ((*in)[*i] == '$' || (*in)[*i] == '`'
			|| (((*in)[*i] == '<' || (*in)[*i] == '>') && (*in)[*i + 1] == '('))
	{
		if ((ret = unquoted_var(in, i, ctxt, quotes)) != SUCCESS)
			return (ret);
	}
	else if ((*in)[*i] == '\\' && (*in)[*i + 1] == '\n')
		ft_strdelchars((*in) + *i, 0, 2);
	else
	{
		if (t_quote_add_new(quotes, *i, (*in) + *i, 1))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_scan"));
		*i += 2;
	}
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
	int		new_quote[2];

	new_quote[0] = index;
	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index] != '<' && (*input)[index] != '>'
		&& (*input)[index] != '`' && (*input)[index])
		index++;
	new_quote[1] = index;
	if ((ret = sh_quote_original_input(
					input, &index, quotes, new_quote)) != SUCCESS)
		return (ret);
	if ((*input)[index] == '\0')
	{
		sh_expansions_update_quotes_pointer(input, (t_quote **)quotes->tbl);
		return (SUCCESS);
	}
	if ((ret = sh_manage_special_char(
					input, &index, context, quotes)) != SUCCESS)
		return (ret);
	return (sh_expansions_scan(input, index, context, quotes));
}
