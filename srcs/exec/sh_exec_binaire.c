/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_binaire.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/30 01:37:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** For each process in the current job-
**	We add that process to the current job group.
** Current job is designated by the g_job_ctrl->curr_job.
** This needs to be done by both the child and the parent processe-
** 	in order to avoid any possible race-conditions.
** First process of each job is appointed as the group leader.
** Example: ls | wc ; echo done
** "ls" and "wc" are in the same process group (with "ls" as the leader)
** "echo" is in another process group (and it's its leader).
*/

#include "sh_21.h"
#include "sh_job_control.h"


static int		do_pre_exc_job_add(t_context *context)
{
	int		ret;

	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if (g_job_ctrl->jc_enabled && g_job_ctrl->job_added == 0)
	{
		if ((ret = jobs_add(1)) != SUCCESS)
			return (ret);
		g_job_ctrl->job_added = 1;
	}
	return (SUCCESS);
}

static int		sh_exec_child_part(t_context *context)
{
	pid_t	cpid;
	int		ret;

	if (g_job_ctrl->jc_enabled && g_job_ctrl->curr_job->pipe_node != PIPE_JOB)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	sh_execute_binary(context);
	return (SUCCESS);
}

static int		sh_exec_parent_part(pid_t cpid, t_context *context)
{
	int		ret;

	if (g_job_ctrl->jc_enabled
		&& g_job_ctrl->curr_job->pipe_node != PIPE_JOB)
	{
		if ((ret = set_pgid_parent(cpid, context)) != SUCCESS)
			return (ret);
		if (g_job_ctrl->curr_job->foreground == 0)
			ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
			return (ret);
	}
	else
		waitpid(cpid, &ret, 0);
	if (g_job_ctrl->jc_enabled && g_job_ctrl->curr_job &&
			g_job_ctrl->curr_job->pipe_node != PIPE_JOB)
		g_job_ctrl->job_added = 0;
	sh_env_update_ret_value_wait_result(context, ret);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
	g_glob.command_line.interrupted = WIFSIGNALED(ret);
	return (SUCCESS);
}

int		sh_exec_binaire(t_context *context)
{
	int			ret;
	pid_t		cpid;


	if ((ret = do_pre_exc_job_add(context)) != SUCCESS)
		return (ret);
	if ((cpid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (cpid == 0)
	{
		if ((ret = sh_exec_child_part(context)) != SUCCESS)
			return (ret);
	}
	else
	{
		if ((ret = sh_exec_parent_part(cpid, context)) != SUCCESS)
			return (ret);
	}
	return (SUCCESS);
}