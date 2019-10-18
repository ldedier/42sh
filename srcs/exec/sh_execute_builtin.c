/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/17 18:48:02 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_exec_builtin:
**	Execute a builtin function, update $? env variable.
**
**	return Value:
**		FAILURE : termcaps error (sh_reset_shell(0) == -1)
**		any value returned by a builtin function
*/

int			sh_execute_builtin(t_ast_node *father_node, t_context *context)
{
	int		res;

	if (isatty(0) && sh_reset_shell(0) == -1)
		return (FAILURE);
	if ((res = loop_traverse_redirection(father_node, context)) != SUCCESS)
	{
		sh_env_update_ret_value(context->shell, res);
		return (res);
	}
	res = context->builtin(context);
	if (res == SUCCESS)
		sh_env_update_ret_value(context->shell, SH_RET_SUCCESS);
	else if (res == BLT_TEST_ERROR)
		sh_env_update_ret_value(context->shell, BLT_TEST_ERROR);
	else
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
	if (isatty(0) && sh_set_shell_back(0) == ATTR_ERROR)
		return (sh_perror("Could not modify this terminal attributes", NULL));
	return (res);
}
