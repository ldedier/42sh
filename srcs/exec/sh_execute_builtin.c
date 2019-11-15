/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:34:44 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/14 12:25:35 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	execute_builtin(t_ast_node *parent_node, t_context *context)
{
	int	res;

	// ft_dprintf(g_term_fd, BLUE"sh_execute_binary: %d\n"EOC, g_job_ctrl->job_added);
	if (IS_FG(context->cmd_type) && sh_pre_execution() != SUCCESS)
		return (FAILURE);
	ft_dprintf(g_term_fd, YELLOW"Prefix in Builtin\n"EOC);	
	if (g_job_ctrl->interactive)
		signal(SIGINT, handle_int);
	if ((res = loop_traverse_redirection(parent_node, context)) != SUCCESS)
	{
		if (IS_FG(context->cmd_type) && sh_post_execution() != SUCCESS)
			return (FAILURE);
		ft_dprintf(g_term_fd, YELLOW"Postfix in Builtin\n"EOC);	
		sh_env_update_ret_value(context->shell, res);
		return (res);
	}
	res = context->builtin(context);
	if (IS_FG(context->cmd_type) && sh_post_execution() != SUCCESS)
		return (FAILURE);
	ft_dprintf(g_term_fd, YELLOW"Postfix in Builtin\n"EOC);	
	return (res);
}

/*
** sh_exec_builtin:
**	Execute a builtin function, update $? env variable.
**	If the builtin command is launched in the background, we fork.
**
**	return Value:
**		FAILURE : termcaps error (sh_reset_shell(0) == -1)
**		any value returned by a builtin function
*/

int			sh_execute_builtin(t_ast_node *parent_node, t_context *context)
{
	int		res;

	res = execute_builtin(parent_node, context);
	if (res == SUCCESS)
		sh_env_update_ret_value(context->shell, SH_RET_SUCCESS);
	else if (res == BLT_TEST_ERROR)
		sh_env_update_ret_value(context->shell, BLT_TEST_ERROR);
	else
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
	return (res);
}
