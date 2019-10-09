/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/08 19:24:48 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** First of all, we need to make sure that when we fork, we reset the signals
** And make the terminal recieve signal-generated keys.
** Now we need to make sure that the job is in its own process group.
** This needs to be done by the parent and the child,
**	to avoid any possible race-condition.
** Then the child will execute the rest of its code normally.
*/

static int		and_or_child_part(t_ast_node *node, t_context *context)
{
	pid_t	cpid;
	int		ret;

	reset_signals();
	if (sh_set_term_sig(1) != SUCCESS)
		return (FAILURE);
	cpid = getpid();
	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
	}
	ret = sh_execute_and_or(node, context);
	if (sh_set_term_sig(0) != SUCCESS)
		return (FAILURE);
	exit (ret);
}

/*
** The parent will set the pgid of the child also (race-conditions)
** Then if the the jobs is in the background, no further actions are taken.
** If the job is in the foreground,
**	the parent will give the job control of terminal.
** Then it will wait for it.
*/

static int		and_or_parent_part(pid_t cpid, t_context *context)
{
	int		ret;

	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_parent(cpid)) != SUCCESS)
			return (ret);
		if (g_job_ctrl->curr_job->foreground == 0)
			ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
			return (ret);
	}
	sh_env_update_ret_value_wait_result(context, ret);
	return (SH_RET_VALUE_EXIT_STATUS(ret));
}

/*
** sh_traverse_and_or :
** This is the browser of the t_list and_or (grammar)
** We execute a and_or node, check it return value and
** execute or not the next and_or node follow the found token
** AND_IF or OR_IF.
**
** We also call the function sh_env_update_question_mark to be sur
** that at this time, the return value is set in the env variable
*/

int				sh_traverse_and_or(t_ast_node *node, t_context *context)
{
	int		ret;
	t_list	*ptr;
	pid_t	cpid;

	ptr = node->children;
	// If no jobs are added, it means that there is no "&" present at the end of the command.
	// If no jobs are added, or no "||" or "&&" are found, proceed as normal.
	if (g_job_ctrl->job_added == 0 || ptr->next == NULL)
	{
		ret = sh_execute_and_or(node, context);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
		return (ret);
	}
	// If we arrive here, it means that there is a command of the forme: cmd1 [|| &&] cmd2 &
	// In this case, we need to fork.
	// (All background commands need to be executed in a subshell).
	g_job_ctrl->curr_job->simple_cmd = 0;
	if ((cpid = fork()) < 0)
		return (sh_perror(SH_ERR1_FORK, "sh_traverse_and_or"));
	if (cpid == 0)
		return (and_or_child_part(node, context));
	else
		return (and_or_parent_part(cpid, context));
}
