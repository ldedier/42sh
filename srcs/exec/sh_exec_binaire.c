/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_binaire.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/21 11:32:47 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** For each process in the current job-
**	We add that process to the current job group.
** Current job is designated by the g_job_ctrl->curr_job.
** This needs to be done by both the child and the parent processe-
** 	in order to avoid any possible race-conditions.
** First process of each job is appointed as the group leader.
** Example: ls | wc ; cat
** "ls" and "wc" are in the same process group (with "ls" as the leader)
** "cat" is in another process group (and it's its leader).
*/

#include "sh_21.h"
#include "sh_job_control.h"

static int		sh_exec_child_part(t_ast_node *father_node, t_context *context)
{
	pid_t	cpid;
	int		ret;

	cpid = getpid();
	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	sh_execute_binary(father_node, context);
	return (SUCCESS);
}

/*
** If the command is piped or is an and_or command,
**	we don't need to put the child in a process group.
** Because it will be forked from within another fork.
** If the shell is non-interactive, we use a simple wait with context->wait_flag-
**	which had been set before.
*/

static int		sh_exec_parent_part(pid_t cpid, t_context *context)
{
	int		ret;

	// If shell is interactive, waiting should be for the whole job.
	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_parent(cpid)) != SUCCESS)
			return (ret);
		if (g_job_ctrl->curr_job->foreground == 0)
			ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
			return (ret);
	}
	// If not, we wait for each process individually.
	else
	{
		// ft_dprintf(g_term_fd, "waitflags: %d\n", context->wflags);
		waitpid(cpid, &ret, context->wflags);
	}
	sh_env_update_ret_value_wait_result(context, ret);
	// to ldedier: Signals can come from outside the terminal (kill)
	// Not sure if we can make the difference between ctrl_c or kill (SIGINT)
	// If we hit ctrl_z, the process is stopped but not signaled.
	g_glob.command_line.interrupted = WIFSIGNALED(ret) || WIFSTOPPED(ret);
	return (SUCCESS);
}

/*
** If no jobs are added when we arrive here, then it's a simple command.
** We fork, the child will put itself in its own process group.
** The parent will also put the child in its own process group.
** Then the parent will put the job in the foreground, and wait for it.
*/

//int		sh_exec_binaire(t_context *context)
int		sh_exec_binaire(t_ast_node *father_node, t_context *context)
{
	pid_t		cpid;

	if (g_job_ctrl->interactive && g_job_ctrl->curr_job->foreground)
		if (sh_pre_execution() != SUCCESS)
			return (FAILURE);
	// Since we already fork for each command in a pipeline, we don't need to fork again.
	if (IS_PIPE(context->cmd_type))
		sh_execute_binary(father_node, context);
	if ((cpid = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (cpid == 0)
		return (sh_exec_child_part(father_node, context));
	else
		return (sh_exec_parent_part(cpid, context));
	return (SUCCESS);
}
