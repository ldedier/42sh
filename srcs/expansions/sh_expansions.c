/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:59:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/29 11:33:38 by jdugoudr         ###   ########.fr       */
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

static int	quote_expansion(
	char **input, int *index, char c, t_context *context)
{
	int	ret;

	ft_strcpy(*input + *index, *input + *index + 1);
	while ((*input)[*index] != c)
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
	ft_strcpy(*input + *index, *input + *index + 1);
	return (SUCCESS);
}

static int	sh_scan_expansions(char **input, int index, t_context *context)
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
		if ((ret = sh_unquoted_var(input, &index, context)) != SUCCESS)
			return (ret);
	}
	else
		backslash(*input, &index, 0);
	return (sh_scan_expansions(input, index, context));
}

/*
** sh_expansions:
**	Mother function of expansions process. Read the current token in context,
**	and perform various expansions on it. It first detect its category,
**	then perform it, and finally replace original value by result.
**
**	Returned Values:
**		FAILURE : malloc error, see ${?} or ${:?}
**		ERROR : bad expansion detected, see ${?} or ${:?}
**		SUCCESS : expansion successfuly replaced in
*/

int			sh_expansions(t_context *context, t_ast_node *node)
{
	char	**input;
	int		ret;
	int		index;

	if (!node || !node->token || !node->token->value)
		return (SUCCESS);
	index = 0;
	input = &node->token->value;
//<<<<<<< HEAD
//	if ((*input)[0] == '~'
//		&& (ret = sh_expansions_process_tilde(
//			input, *input, context)) != SUCCESS)
//	{
//		if (sh_env_update_ret_value_and_question(context->shell, ret))
//			return (FAILURE);
//		return (ret);
//	}
//	ret = sh_scan_expansions(input, index, context);
//	if (ret != SUCCESS)
//		if (sh_env_update_ret_value_and_question(context->shell, ret))
//			return (FAILURE);
//	return (ret);
//=======
	ret = SUCCESS;
	if ((*input)[0] == '~')
		ret = sh_expansions_process_tilde(input, *input, context);
	if (!ret)
		ret = sh_scan_expansions(input, index, context);
	if (ret == ERROR || ret == FAILURE)
		sh_env_update_ret_value(context->shell, ret);
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	if (ret)
		return (ret);
	return (sh_expansions_splitting(node, context));
//>>>>>>> 1687fa0e723590168a9e38a53c43c82ac40330a4
}
