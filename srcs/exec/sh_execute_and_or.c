/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_and_or.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:54:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** If the command is of the type cmd1 || cmd2.
** Shell is interactive:
** 	1- job in fg, cmd1 fails or is killed by any signal other than SIGINT.
** Shell is non-interactive:
**	if cmd1 fails or is killed by ANY signal.
*/

static int		should_execute(int prev_symb, int ret)
{
	int	ret_sig;
	int	ret_exit;
	int	result;

	ret_sig = SH_RET_VALUE_SIG_RECEIVED(ret);
	ret_exit = SH_RET_VALUE_EXIT_STATUS(ret);
	if (prev_symb == -1)
		return (1);
	if (prev_symb == sh_index(LEX_TOK_AND_IF))
		return (!ret);
	else if (g_job_ctrl->interactive)
	{
		result = ret_exit || (ret_sig != 130 && ret_sig != 0);
		return (result);
	}
	return (ret);
}

/*
** sh_traverse_and_or_call_sons_exec :
** Following return value of the preview execution,
** this function execute or not the next level in the ast,
** pipe line (sh_traverse_pipe_sequence).
*/

static long		sh_traverse_and_or_call_sons_exec(t_ast_node *node,
		int *prev_symbol, t_context *context)
{
	int			ret;

	if (!should_execute(*prev_symbol, context->shell->ret_value))
		return (SUCCESS);
	ret = sh_traverse_pipeline(node, context);
	if (ret == BLT_TEST_ERROR || context->shell->ret_value == BLT_TEST_ERROR)
	{
		context->shell->ret_value_set = 0;
		sh_env_update_ret_value(context->shell, 2);
	}
	if (ret == FAILURE || ret == STOP_CMD_LINE || !context->shell->running)
		return (ret);
	return (SUCCESS);
}

/*
** sh_traverse_and_or_process_phase :
** This function set the env variable with the return value of the
** and_or node execution.
*/

static long		sh_traverse_and_or_process_phase(
		t_context *context, int prev_symbol, t_list *ptr)
{
	int			ret;
	t_ast_node	*child;

	child = (t_ast_node*)ptr->content;
	ret = sh_traverse_and_or_call_sons_exec(child, &prev_symbol, context);
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	if (ret == KEEP_READ || ret == STOP_CMD_LINE || ret == FAILURE)
		return (ret);
	if (ret == ERROR)
		return (KEEP_READ);
	return (KEEP_READ);
}

int				sh_execute_and_or(t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	int			ret;
	int			prev_symbol;

	ptr = node->children;
	prev_symbol = -1;
	while (ptr != NULL && context->shell->running)
	{
		if (ptr->next == NULL)
		{
			context->cmd_type |= (g_job_ctrl->ampersand ? BG_NODE : 0);
			context->wflags = (g_job_ctrl->ampersand ? WNOHANG : 0);
		}
		if ((ret = sh_traverse_and_or_process_phase(
						context, prev_symbol, ptr)) != KEEP_READ)
			return (ret);
		if ((ptr = (ptr)->next))
		{
			prev_symbol = ((t_ast_node*)ptr->content)->symbol->id;
			ptr = (ptr)->next;
		}
		t_context_reset(context);
	}
	return (SUCCESS);
}
