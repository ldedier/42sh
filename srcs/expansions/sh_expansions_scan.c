/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:32:53 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/05 11:05:39 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	backslash(char *input, int *index, int quoted)
{
	if (quoted)
	{
		if (input[*index + 1] == '$' || input[*index + 1] == '"'
			|| input[*index + 1] == '\\')
			ft_strcpy(input + *index, input + *index + 1);
		else if (input[*index + 1] == '\n')
			ft_strcpy(input + *index, input + *index + 2);
	}
	else
		ft_strcpy(input + *index, input + *index + 1);
	(*index) += 1;
}

static int	doble_quote_removal(
	char **input, int *index, int do_expansion, t_context *context)
{
	int	ret;

	ft_strcpy(*input + *index, *input + *index + 1);
	while ((*input)[*index] != '\"')
	{
		if ((*input)[*index] == '$' && do_expansion)
		{
			if ((ret = sh_expansions_process(
				input, *input + *index, context, index)) != SUCCESS)
			{
				if (sh_env_update_ret_value_and_question(context->shell, ret))
					return (FAILURE);
				return (ret);
			}
		}
		else if ((*input)[*index] == '\\')
			backslash(*input, index, 1);
		else
			*index += 1;
	}
	ft_strcpy(*input + *index, *input + *index + 1);
	return (SUCCESS);
}

static void	quote_removal(char **input, int *index)
{
	ft_strcpy(*input + *index, *input + *index + 1);
	while ((*input)[*index] != '\'')
		*index += 1;
	ft_strcpy(*input + *index, *input + *index + 1);
}

/*
** sh_scan_expansions:
** Scan input, starting at index
** Remove quote, doble quote and backslah.
** Replace variable with looking in context variables.
*/

int			sh_expansions_scan(
		char **input, int index, int do_expansion, t_context *context)
{
	int	ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'')
		quote_removal(input, &index);
	else if ((*input)[index] == '"')
	{
		if ((ret = doble_quote_removal(
			input, &index, do_expansion, context)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '$' && do_expansion)
	{
		if ((ret = sh_unquoted_var(input, &index, context)) != SUCCESS)
			return (ret);
	}
	else
		backslash(*input, &index, 0);
	return (sh_expansions_scan(input, index, do_expansion, context));
}
