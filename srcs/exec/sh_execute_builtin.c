/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 11:49:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"



static int	execute_child_part(pid_t cpid, t_context *context)
{
	int		ret;

	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	ret = context->builtin(context);
	exit(ret);
}

static int	execute_parent_part(pid_t cpid)
{
	int	ret;

	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_parent(cpid)) != SUCCESS)
			return (ret);
		if ((ret = job_put_in_bg(g_job_ctrl->curr_job, 0)) != SUCCESS)
			return (FAILURE);
		g_job_ctrl->job_added = 0;
	}
	return (SUCCESS);
}

static int	execute_builting_in_bg(t_context *context)
{
	pid_t	cpid;

	if ((cpid = fork()) < -1)
		return(sh_perror(SH_ERR1_FORK, "sh_execute_builtin"));
	if (cpid == 0)
		return (execute_child_part(cpid, context));
	return (execute_parent_part(cpid));
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

int			sh_execute_builtin(t_ast_node *father_node, t_context *context)
{
	int		res;

	if (g_job_ctrl->interactive && sh_reset_shell(0) != SUCCESS)
		return (FAILURE);
	if (context->cmd_type == (SIMPLE_NODE | BG_NODE))
		res = execute_builting_in_bg(context);
	else
	{
		if ((res = loop_traverse_redirection(father_node, context)) != SUCCESS)
		{
			sh_env_update_ret_value(context->shell, res);
			return (res);
		}
		res = context->builtin(context);
	}
	if (res == SUCCESS)
		sh_env_update_ret_value(context->shell, SH_RET_SUCCESS);
	else if (res == BLT_TEST_ERROR)
		sh_env_update_ret_value(context->shell, BLT_TEST_ERROR);
	else
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
	if (g_job_ctrl->interactive && sh_set_shell_back(0) == ATTR_ERROR)
		return (sh_perror("Could not modify this terminal attributes", NULL));
	return (res);
}
