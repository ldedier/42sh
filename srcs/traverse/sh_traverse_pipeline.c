/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 18:24:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_pipe_sequence :
** We check what if we have pipe to do in the
** pipe sequence.
*/

static long	sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	int	ret;

	sh_traverse_tools_show_traverse_start(node, context);
	if (ft_lstlen(node->children) > 1)
	{
		if (g_job_ctrl->interactive && !g_job_ctrl->job_added)
		{
			if ((ret = job_add(node, NULL, IS_BG(context->cmd_type))))
			{
				sh_env_update_ret_value(context->shell, ret);
				return (ret);
			}
			g_job_ctrl->job_added = 1;
		}
		context->cmd_type |= PIPE_NODE;
		ret = sh_execute_pipe(node, context);
		context->cmd_type &= ~PIPE_NODE;
		if (g_job_ctrl->interactive)
			g_job_ctrl->job_added = 0;
	}
	else
		ret = sh_traverse_command(node->children->content, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}

/*
** sh_traverse_pipe_line :
** This is the browser of t_list pipe_line
** We check for a bang, then
** We check if we have separator pipe
** If we don't, we just call the next level on the ast simple_command
** If we have, we do the first fork here and call the pipe_sequence_execute
** wich will perform all pipe and call traverse_command for each sons.
**
** We update the env question_mark at this point.
*/

long		sh_traverse_pipeline(t_ast_node *node, t_context *context)
{
	int			ret;
	int			bang;
	t_ast_node	*child;

	sh_traverse_tools_show_traverse_start(node, context);
	bang = 0;
	child = node->children->content;
	if (child->symbol->id == sh_index(LEX_TOK_BANG))
	{
		child = node->children->next->content;
		bang = 1;
	}
	ret = sh_traverse_pipe_sequence(child, context);
	if (bang)
	{
		if (context->shell->ret_value != 0)
			context->shell->ret_value = 0;
		else
			context->shell->ret_value = 1;
	}
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
