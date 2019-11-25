/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:34:44 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/25 22:39:48 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	execute_child_part(
		pid_t cpid, t_ast_node *parent_node, t_context *context)
{
	int	ret;

	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	reset_signals();
	g_job_ctrl->interactive = 0;
	if ((ret = loop_traverse_redirection(parent_node, context)) != SUCCESS)
		return (ret);
	ret = context->builtin(context);
	g_job_ctrl->interactive = 1;
	free_execution_tools(&context->shell->exec->tokens,
		&context->shell->exec->ast_root, &context->shell->exec->cst_root);
	sh_free_all(context->shell);
	ft_strdel(&context->shell->hist_dup);
	free(context->cmd_string);
	t_context_free_content(context);
	return (ret);
}

static int	execute_parent_part(pid_t cpid)
{
	if (g_job_ctrl->interactive)
	{
		if (set_pgid_parent(cpid) != SUCCESS)
			return (FAILURE);
		if (job_put_in_bg(g_job_ctrl->curr_job) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	execute_builtin_in_bg(t_ast_node *parent_node, t_context *context)
{
	pid_t	cpid;
	int		ret;

	if (g_job_ctrl->interactive && !g_job_ctrl->job_added)
	{
		if ((ret = job_add(parent_node, context->cmd_string,
			IS_BG(context->cmd_type))) != SUCCESS)
			return (ret);
		g_job_ctrl->job_added = 1;
	}
	if ((cpid = fork()) < -1)
		return (sh_perror(SH_ERR1_FORK, "sh_execute_builtin"));
	else if (cpid == 0)
		exit(execute_child_part(cpid, parent_node, context));
	else
	{
		ret = execute_parent_part(cpid);
		if (g_job_ctrl->interactive)
			g_job_ctrl->job_added = 0;
	}
	return (ret);
}

static int	executing_builtin(t_ast_node *parent_node, t_context *context)
{
	int	res;

	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if (g_job_ctrl->interactive)
		signal(SIGINT, handle_int);
	if ((res = loop_traverse_redirection(parent_node, context)) != SUCCESS)
	{
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		sh_env_update_ret_value(context->shell, res);
		return (res);
	}
	res = context->builtin(context);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
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

	context->is_builtin = 1;
	if (context->cmd_type == (SIMPLE_NODE | BG_NODE))
		res = execute_builtin_in_bg(parent_node, context);
	else
		res = executing_builtin(parent_node, context);
	if (res == SUCCESS)
		sh_env_update_ret_value(context->shell, SH_RET_SUCCESS);
	else if (res == BLT_TEST_ERROR)
		sh_env_update_ret_value(context->shell, BLT_TEST_ERROR);
	else
		sh_env_update_ret_value(context->shell, SH_RET_ERROR);
	return (res);
}
