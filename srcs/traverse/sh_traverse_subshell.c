/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:03:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/26 15:34:18 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	child_part(t_ast_node *node, t_context *context)
{
	int			ret;
	t_ast_node	*compound_redir;
	t_list		*lst_redi;

	ret = 0;
	if (g_job_ctrl->interactive)
	{
		if (set_pgid_child(getpid()) != SUCCESS)
			exit (FAILURE);
	}
	reset_signals();
	g_job_ctrl->interactive = 0;
	if ((ret = sh_traverse_tools_compound_redir(
					node, context, &compound_redir, &lst_redi)))
		return (ret);
	ret = sh_traverse_tools_search_term(node, context);
	if (sh_reset_redirection(&lst_redi))
		return (FAILURE);
	g_job_ctrl->interactive = 1;
	sh_free_all(context->shell);
	if (ret != SUCCESS)
		exit(ret);
	exit(context->shell->ret_value);
}

static int	parents_part(pid_t pid, t_context *context)
{
	int	ret;

	ret = 0;
	if (g_job_ctrl->interactive)
	{
		if (set_pgid_parent(pid) != SUCCESS)
			return (FAILURE);
		if (g_job_ctrl->curr_job->foreground)
		{
			if (sh_pre_execution() != SUCCESS)
				return (FAILURE);
			if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
				return (FAILURE);
		}
		else if (job_put_in_bg(g_job_ctrl->curr_job, 0) != SUCCESS)
			return (FAILURE);
	}
	else
		waitpid(pid, &ret, context->wflags);
	if (sh_post_execution() != SUCCESS)
				return (FAILURE);
	sh_env_update_ret_value_wait_result(context, ret);
	return (SUCCESS);
}

/*
** sh_traverse_subshell
** We execute here what a subshell do.
** We fork to have a "subshell"
**
** A subshell node can only have, at least and at most,
** '(' 'compund_list' and ')' children.
** So we can directly go to compound_list node.
*/

int		sh_traverse_subshell(t_ast_node *node, t_context *context)
{
	pid_t	pid;
	int		ret;

	if (g_job_ctrl->interactive && !g_job_ctrl->job_added)
	{
		if (job_add(IS_BG(context->cmd_type)) != SUCCESS)
			return (FAILURE);
		g_job_ctrl->job_added = 1;
	}
	if ((pid = fork()) < 0)
		return (sh_perror_err(SH_ERR1_FORK, "can't fork for subshell"));
	else if (pid)
	{
		ret = parents_part(pid, context);
		g_job_ctrl->job_added = 0;
		return (ret);
	}
	else
		child_part(node, context);
	return (0);
}
