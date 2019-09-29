/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_binaire.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/29 16:57:29 by mdaoud           ###   ########.fr       */
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
	int		res;

	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if (g_job_ctrl->jc_enabled && g_job_ctrl->job_added == 0)
	{
		if ((res = jobs_add(1)) != SUCCESS)
			return (res);
		ft_printf("job added in exec_binary\n");
		g_job_ctrl->job_added = 1;
	}
	return (SUCCESS);
}

static int		sh_exec_child_part(t_context *context)
{
	pid_t	cpid;

	if (g_job_ctrl->jc_enabled)
	{
		cpid = getpid();
		set_child_pgid(cpid);
		if (g_job_ctrl->curr_job->foreground == 1)
			if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->curr_job->pgid) < 0)
				return (jc_error_free("tcsetpgrp",
					"Could not give terminal control to the process", 1, FAILURE));
	}
	// kill(g_job_ctrl->shell_pgid, SIGUSR1);
	sh_execute_binary(context);
	return (SUCCESS);
}

static int		sh_exec_parent_part(pid_t cpid, t_context *context)
{
	int		res;

	if (g_job_ctrl->jc_enabled)
	{
		if ((res = process_add(context, cpid)) != SUCCESS)
			return (res);
		if ((res = set_child_pgid(cpid)) != SUCCESS)
			return (res);
		ft_dprintf(1, "Added process: %s", (char **)context->params->tbl[0]);
		ft_dprintf(1, "\tpid: %d, pgid: %d\n", cpid, getpgid(cpid));
		if (g_job_ctrl->curr_job->foreground == 0)
			res = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &res) != SUCCESS)
			return (res);
	}
	else
		waitpid(cpid, &res, 0);
	if (g_job_ctrl->jc_enabled)
		g_job_ctrl->job_added = 0;
	sh_env_update_ret_value_wait_result(context, res);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
	g_glob.command_line.interrupted = WIFSIGNALED(res);
	return (SUCCESS);
}

int		sh_exec_binaire(t_context *context)
{
	int			res;
	pid_t		cpid;


	if ((res = do_pre_exc_job_add(context)) != SUCCESS)
		return (res);
	if ((cpid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (cpid == 0)
	{
		if ((res = sh_exec_child_part(context)) != SUCCESS)
			return (res);
	}
	else
	{
		if ((res = sh_exec_parent_part(cpid, context)) != SUCCESS)
			return (res);
	}
	return (SUCCESS);
}