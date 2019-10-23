/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:03:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/23 11:27:09 by jdugoudr         ###   ########.fr       */
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
	sh_free_all(context->shell);
	if (ret != SUCCESS)
		exit(ret);
	exit(context->shell->ret_value);
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
			if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
				return (FAILURE);
		}
		else if (job_put_in_bg(g_job_ctrl->curr_job, 0) != SUCCESS)
			return (FAILURE);
	}
	else
		waitpid(pid, &ret, context->wflags);
	sh_env_update_ret_value_wait_result(context, ret);
	return (SUCCESS);
}

int		sh_traverse_subshell(t_ast_node *node, t_context *context)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (sh_perror_err(SH_ERR1_FORK, "can't fork for subshell"));
	else if (pid)
		return (parents_part(pid, context));
	else
		child_part(node, context);
	return (0);
}
