/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_ampersand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:27:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 13:23:56 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


static int	child_part(t_ast_node *node, t_context *context)
{
	pid_t	cpid;
	int		ret;
	
	reset_signals();
	cpid = getpid();
	context->wflags = 0;
	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	// g_job_ctrl->interactive = 0;
	ret = sh_execute_and_or(node, context);
	// g_job_ctrl->interactive = 1;
	sh_free_all(context->shell);
	return (ret);
}

static int	parent_part(t_context *context, pid_t cpid)
{
	int		ret;

	if (g_job_ctrl->interactive)
	{
		if (set_pgid_parent(cpid) != SUCCESS)
			return (FAILURE);
		else if (g_job_ctrl->curr_job->foreground == 0)
		{
			if ((ret = job_put_in_bg(g_job_ctrl->curr_job)) != SUCCESS)
				return (ret);
		}
	}
	else
		waitpid(cpid, &ret, context->wflags);
	sh_env_update_ret_value_wait_result(context, ret);
	return (SUCCESS);
}

/*
** sh_traverse_ampersand :
** This function it's called when we find a semi_col in
** the t_list LIST (grammar)
** It take the context and the and_or node to execute.
*/
int	sh_traverse_ampersand(t_ast_node *node, t_context *context)
{
	int		ret;
	pid_t	cpid;


	context->wflags = WNOHANG;
	context->cmd_type |= BG_NODE;
	if (g_job_ctrl->cmd_subst)
		context->wflags = 0;
	if (g_job_ctrl->interactive && !g_job_ctrl->job_added)
	{
		if ((ret = job_add(node, NULL, 1)) != SUCCESS)
			return (ret);
		g_job_ctrl->job_added = 1;
		if ((cpid = fork()) < 0)
			return (sh_perror(SH_ERR1_FORK, "sh_traverse_ampersand"));
		else if (cpid == 0)
			exit(child_part(node, context));
		else
		{
			// ft_dprintf(g_term_fd, "Shell pgid: %d\n<%d> Forked for ampersand <%d>\n", g_job_ctrl->shell_pgid, getpid(), cpid);
			ret = parent_part(context, cpid);
		}
		if (g_job_ctrl->interactive)
			g_job_ctrl->job_added = 0;
		return (ret);
	}
	ret = sh_traverse_and_or(node, context);
	return (ret);
}
