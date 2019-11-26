/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 10:03:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/26 08:02:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	child_part(t_ast_node *node, t_context *context)
{
	int			ret;
	t_ast_node	*compound_redir;
	t_list		*lst_redi;

	if (g_job_ctrl->interactive)
	{
		if (set_pgid_child(getpid()) != SUCCESS)
			exit(FAILURE);
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
	t_context_free_content(context);
	free_execution_tools(&context->shell->exec->tokens,
		&context->shell->exec->ast_root, &context->shell->exec->cst_root);
	sh_free_all(context->shell);
	if (ret != SUCCESS)
		exit(ret);
	exit(context->shell->ret_value);
}

static int	parents_part(pid_t pid, t_context *context)
{
	int	ret;
	int	fun_ret;

	ret = 0;
	if (g_job_ctrl->interactive)
	{
		if (set_pgid_parent(pid) != SUCCESS)
			return (FAILURE);
		if (g_job_ctrl->curr_job->foreground)
		{
			if (sh_pre_execution() != SUCCESS)
				return (FAILURE);
			if ((fun_ret = job_put_in_fg(g_job_ctrl->curr_job, 0, &ret)))
				return (fun_ret);
		}
		else if (job_put_in_bg(g_job_ctrl->curr_job) != SUCCESS)
			return (FAILURE);
	}
	else
		waitpid(pid, &ret, context->wflags);
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

long		sh_traverse_subshell(t_ast_node *node, t_context *ctxt)
{
	pid_t	pid;
	int		ret;

	if (IS_PIPE(ctxt->cmd_type))
		return (child_part(node, ctxt));
	ctxt->is_builtin = 0;
	if (g_job_ctrl->interactive && !g_job_ctrl->job_added)
	{
		if ((ret = job_add(node->parent->parent, NULL, IS_BG(ctxt->cmd_type))))
			return (ret);
		g_job_ctrl->job_added = 1;
	}
	if ((pid = fork()) < 0)
		return (sh_perror_err(SH_ERR1_FORK, "can't fork for subshell"));
	else if (pid)
	{
		ret = parents_part(pid, ctxt);
		g_job_ctrl->job_added = 0;
		return (ret);
	}
	else
		child_part(node, ctxt);
	return (0);
}
