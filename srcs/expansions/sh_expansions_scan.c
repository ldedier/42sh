/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_scan.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:17:39 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/04 15:16:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	backslash(char *input, int *index, int quoted)
{
	if (quoted)
	{
		if (input[*index + 1] == '$' || input[*index + 1] == '"'
			|| input[*index + 1] == '\\')
			ft_strdelchars(input, *index, 1);
		else if (input[*index + 1] == '\n')
			ft_strdelchars(input, *index, 2);
	}
	else
		ft_strdelchars(input, *index, 1);
	(*index) += 1;
}

static int	quote_expansion(
	char **input, int *index, char c, t_context *context)
{
	int	ret;

	ft_strdelchars(*input, *index, 1);
	while ((*input)[*index] != c && (*input)[*index])
	{
		if (c == '"' && (*input)[*index] == '$')
		{
			if ((ret = sh_expansions_process(
				input, *input + *index, context, index)) != SUCCESS)
			{
				if (sh_env_update_ret_value_and_question(context->shell, ret))
					return (FAILURE);
				return (ret);
			}
		}
		else if (c == '"' && (*input)[*index] == '\\')
			backslash(*input, index, 1);
		else
			*index += 1;
	}
	if (!(*input)[*index])
		return (ERROR);
	ft_strdelchars(*input, *index, 1);
	return (SUCCESS);
}

static int	unquoted_var(char **input, int *index, t_context *context, t_ast_node *node)
{
	int	ret;

	if ((ret = sh_expansions_process(
		input, *input + *index, context, index)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(context->shell, ret))
			return (FAILURE);
		return (ret);
	}
	(void)node;
	return (SUCCESS);
}

/*
** sh_scan_expansions:
** Scan input, starting at index
** Remove quote, doble quote and backslah.
** Replace variable with looking in context variables.
**
** Returned Values :
**	ERROR : Bad expansion format detected
**	FAILURE : Malloc Error
**	STOP_CMD_LINE : ${?} or ${:?} returned an error => stop current line
**	SUCCESS : Successfully processed and repalced expansion by it's result.
*/

int			sh_expansions_scan(char **input, int index, t_context *context, t_ast_node *node)
{
	int	ret;

	while ((*input)[index] != '\'' && (*input)[index] != '"'
		&& (*input)[index] != '\\' && (*input)[index] != '$'
		&& (*input)[index])
		index++;
	if ((*input)[index] == '\0')
		return (SUCCESS);
	if ((*input)[index] == '\'' || (*input)[index] == '"')
	{
		if ((ret = quote_expansion(
			input, &index, (*input)[index], context)) != SUCCESS)
			return (ret);
	}
	else if ((*input)[index] == '$')
	{
		if ((ret = unquoted_var(input, &index, context, node)) != SUCCESS)
			return (ret);
	}
	else
		backslash(*input, &index, 0);
	return (sh_expansions_scan(input, index, context, node));
}
