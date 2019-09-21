/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here_expansion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:43:22 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/20 15:51:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** Expansion apply to heredoc
*/

// static int	is_valid_var(char c)
// {
// 	if (ft_isalnum(c))
// 		return (1);
// 	else if (c == '$' || c == '?')
// 		return (1);
// 	else if (c == '{')
// 		return (1);
// 	return (0);
// }

/*
** The epxansion function had been disabled for expansions rework
** Will need to activate it again
*/

int			sh_traverse_io_here_expansion(
		char **str, int *cursor, t_context *context)
{
	// int ret;

	// if ((*str)[*cursor] == '$' && is_valid_var((*str)[*cursor + 1]))
	// {
	// 	if ((ret = sh_expansions_process(
	// 					str, (*str) + *cursor, context, cursor)))
	// 	{
	// 		if (sh_env_update_ret_value_and_question(context->shell, ret))
	// 			return (FAILURE);
	// 		return (ERROR);
	// 	}
	// }
	// else
	(*cursor) += 1;
	return (SUCCESS);
	(void)context;
	(void)cursor;
	(void)str;
}
