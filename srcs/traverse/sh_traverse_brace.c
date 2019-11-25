/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_brace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:34:50 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/25 11:23:58 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	braces_child_part(t_ast_node *node, t_context *context)
{
	t_list		*lst_redi;
	t_ast_node	*compound_redir;
	int			ret;

	if (set_pgid_child(getpid()) != SUCCESS)
		return (FAILURE);
	reset_signals();
	g_job_ctrl->interactive = 0;
	if ((ret = sh_traverse_tools_compound_redir(
					node, context, &compound_redir, &lst_redi)))
		return (ret);
	sh_traverse_tools_search_term(node, context);
	if (sh_reset_redirection(&lst_redi))
		return (FAILURE);
	return (SUCCESS);
}

static int	braces_parent_part(pid_t cpid, t_context *context)
{
	int	ret;

	ret = 0;
	if (g_job_ctrl->interactive)
	{
		if (set_pgid_parent(cpid) != SUCCESS)
			return (FAILURE);
		else if (job_put_in_bg(g_job_ctrl->curr_job) != SUCCESS)
			return (FAILURE);
	}
	else
		waitpid(cpid, &ret, context->wflags);
	sh_env_update_ret_value_wait_result(context, ret);
	return (SUCCESS);
}

static int	sh_execute_brace_bg(t_ast_node *node, t_context *context)
{
	pid_t	cpid;
	int		ret;

	if ((cpid = fork()) < 0)
		return (sh_perror_err(SH_ERR1_FORK, "can't fork for braces"));
	else if (cpid == 0)
		exit(braces_child_part(node, context));
	else
		ret = braces_parent_part(cpid, context);
	return (ret);
}

long		sh_traverse_brace(t_ast_node *node, t_context *ctxt)
{
	int			ret;
	t_ast_node	*compound_redir;
	t_list		*lst_redi;

	sh_traverse_tools_show_traverse_start(node, ctxt);
	ctxt->is_builtin = 1;
	if (g_job_ctrl->interactive && IS_BG(ctxt->cmd_type))
	{
		if ((ret = job_add(node->parent->parent, NULL, IS_BG(ctxt->cmd_type))))
			return (ret);
		g_job_ctrl->job_added = 1;
		ret = sh_execute_brace_bg(node, ctxt);
		g_job_ctrl->job_added = 0;
		return (ret);
	}
	if ((ret = sh_traverse_tools_compound_redir(
					node, ctxt, &compound_redir, &lst_redi)))
		return (ret);
	ret = sh_traverse_tools_search_term(node, ctxt);
	if (sh_reset_redirection(&lst_redi))
		return (FAILURE);
	sh_traverse_tools_show_traverse_ret_value(node, ctxt, ret);
	return (ret);
}
