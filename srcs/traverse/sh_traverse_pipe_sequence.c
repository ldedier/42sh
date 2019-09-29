/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/29 23:42:55 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		pipe_child_part(t_ast_node *node, t_context *context)
{
	pid_t	cpid;
	int		ret;

	reset_signals();
	if (sh_set_term_sig(1) != SUCCESS)
		return (FAILURE);
	cpid = getpid();
	// ft_dprintf(g_job_ctrl->term_fd, "Forked first, %d\n", cpid);
	if (g_job_ctrl->jc_enabled)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	ret = sh_execute_pipe(node, context);
	return (ret);
}

static int		pip_parent_part(pid_t cpid, t_context *context)
{
	int		ret;

	if (g_job_ctrl->jc_enabled)
	{
		if ((ret = set_pgid_parent(cpid, context)) != SUCCESS)
			return (ret);
		if (g_job_ctrl->curr_job->foreground == 0)
			waitpid(cpid, &ret, 0);
		if (g_job_ctrl->curr_job->foreground == 0)
			ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
			return (ret);
	}
	sh_env_update_ret_value_wait_result(context, ret);
	return (SH_RET_VALUE_EXIT_STATUS(ret));
}
/*
 * pipe_to_do :
 * This function is called when we have pipes to execute.
 * We do here the first fork. That's mean, in this case, we have to add
 * this new process in the jobs list.
*/
static int		pipe_to_do(t_ast_node *node, t_context *context)
{
	int		ret;
	int 	cpid;

	if ((cpid = fork()) < 0)
		return (sh_perror(SH_ERR1_FORK, "execution fork for pipe"));
	else if (cpid == 0)
	{
		ret = pipe_child_part(node, context);
		exit(ret);
	}
	else
	{
		ret = pip_parent_part(cpid, context);
		return (ret);
	}
}

/*
 * sh_traverse_pipe_sequence :
 * This is the browser of t_list pipe_sequence
 * We check if we have separator pipe
 * If we don't, we just call the next level on the ast simple_command
 * If we have, we do the first fork here and call the pipe_sequence_execute
 * wich will perform all pipe and call traverse_command for each sons.
*/
int				sh_traverse_pipeline(t_ast_node *node, t_context *context)
{
	int		ret;

	sh_traverse_tools_show_traverse_start(node, context);
	if (ft_lstlen(node->children) > 1)
	{
		if (g_job_ctrl->jc_enabled)
		{
			if (g_job_ctrl->job_added == 0)
			{
				ft_printf("No job added yet, adding ..\n");
				if ((ret = jobs_add(1)) != SUCCESS)
					return (ret);
				g_job_ctrl->job_added = 1;
			}
			g_job_ctrl->curr_job->pipe_node = PIPE_JOB;
		}
		ret = pipe_to_do(node, context);
	}
	else
		ret = sh_traverse_command(node->children->content, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
