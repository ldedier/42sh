/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/11 22:04:04 by mdaoud           ###   ########.fr       */
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

	// reset_signals_and_or();
	reset_signals(); // CHECK
	cpid = getpid();
	if (g_job_ctrl->interactive)
	{
		// ft_printf("%sInteractive shell AND_OR%s\n", BLUE, EOC);
		if ((ret = set_pgid_child(cpid)) != SUCCESS)
			return (ret);
		// ft_dprintf(g_term_fd, "%sChild:\tpid: %d, ppid: %d, pgid: %d%s\n", YELLOW, getpid(), getppid(), getpgid(getpid()), EOC);
	}
	ret = sh_execute_and_or(node, context);
	// ft_dprintf(g_term_fd, "Exiting with %d\n", ret);
	exit (ret);
}

/*
** The parent will set the pgid of the child also (race-conditions)
** Then if the the jobs is in the background, no further actions are taken.
** If the job is in the foreground,
**	the parent will give the job control of terminal.
** Then it will wait for it.
** If shell is non-interactive, we just launch the process in background,
**	We don't have to wait for it to report back.
*/

static int		and_or_parent_part(pid_t cpid, t_context *context)
{
	int		ret;

	if (g_job_ctrl->interactive)
	{
		if ((ret = set_pgid_parent(cpid)) != SUCCESS)
			return (ret);
	// ft_dprintf(g_term_fd, "%sSHELL:\tpid: %d, ppid: %d, pgid: %d%s\n", YELLOW, getpid(), getppid(), getpgid(getpid()), EOC);
	// ft_dprintf(g_term_fd, "%sParent:\tpid: %d, ppid: %d, pgid: %d%s\n", YELLOW, cpid, getppid(), getpgid(cpid), EOC);
		ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
	}
	else
		ret = SUCCESS;
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
	// If there are no && or || present, or the and_or command in the foreround
	// We proceed as normal (No job added).
	if (ptr->next == NULL || !(context->cmd_type & BG_NODE))
	{
		ret = sh_execute_and_or(node, context);
		sh_traverse_tools_show_traverse_ret_value(node, context, ret);
		return (ret);
	}
	// If we arrive here, it means that there is a command of the forme: cmd1 [|| &&] cmd2 &
	// In this case, we need to fork.
	// (All background commands need to be executed in a subshell).
	context->cmd_type &= ~CMD_TYPE;	// Mask to reset the cmd_type
	context->cmd_type |= AND_OR_NODE;
	if ((cpid = fork()) < 0)
		return (sh_perror(SH_ERR1_FORK, "sh_traverse_and_or"));
	if (cpid == 0)
		return (and_or_child_part(node, context));
	else
		return (and_or_parent_part(cpid, context));
}
