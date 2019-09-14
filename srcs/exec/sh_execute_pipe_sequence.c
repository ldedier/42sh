/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_sequence.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 10:45:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 00:14:43 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

void		sh_execute_pipe_sequence_close_pipes_list(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context;

	ptr = contexts;
	while (ptr != NULL)
	{
		context = (t_context *)ptr->content;
		sh_process_execute_close_pipes(context);
		ptr = ptr->next;
	}
}

static int	sh_execute_pipe_sequence_exec_forks(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context_iter;
	pid_t		child_pid;

	ptr = contexts;
	while (ptr != NULL)
	{
		context_iter = (t_context *)ptr->content;
		process_add(context_iter, 0);
		ptr = ptr->next;
	}
	return (SUCCESS);
}

// static int		sh_execute_pipe_sequence_exec_forks(t_list *contexts)
// {
// 	t_list		*ptr;
// 	t_context	*context_iter;
// 	pid_t		child_pid;

// 	ptr = contexts;
// 	while (ptr != NULL)
// 	{
// 		context_iter = (t_context *)ptr->content;
// 		process_add(context_iter, 0);
// 		if ((context_iter->pid = fork()) == -1)
// 		{
// 			sh_execute_pipe_sequence_close_pipes_list(contexts);
// 			return (sh_perror(SH_ERR1_FORK,
// 				"sh_execute_pipe_sequence_exec_forks"));
// 		}
// 		if (context_iter->pid == 0)
// 		{
// 			str_tab_print((char**)context_iter->params->tbl);
// 			sh_execute_child(context_iter, contexts);
// 		}
// 		else
// 		{
// 			g_parent = context_iter->pid;
// 			ptr = ptr->next;
// 		}
// 	}
// 	return (SUCCESS);
// }

static int	sh_execute_pipe_sequence_waits(t_context *context, int *res_save)
{
	pid_t		wpid;
	int			res;

	while ((wpid = wait(&res)) > 0)
	{
		if (wpid == g_parent)
		{
			sh_env_update_ret_value_wait_result(context, res);
			*res_save = res;
		}
	}
	if (sh_env_update_question_mark(context->shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int			sh_execute_pipe_sequence(t_context *context, t_list *contexts)
{
	int		res_save;

	res_save = 0;
	if (sh_pre_execution_pipes(contexts) != SUCCESS)
		return (FAILURE);
	if (sh_execute_pipe_sequence_exec_forks(contexts) == FAILURE)
		return (FAILURE);
	sh_execute_pipe_sequence_close_pipes_list(contexts);
	if (sh_execute_pipe_sequence_waits(context, &res_save) == FAILURE)
		return (FAILURE);
	if (context->current_pipe_sequence_node->
			metadata.pipe_metadata.last_ret_value)
	{
		if (sh_env_update_ret_value_and_question(context->shell, context->
		current_pipe_sequence_node->metadata.pipe_metadata.last_ret_value))
			return (FAILURE);
	}
	g_parent = 0;
	if (isatty(0) && sh_set_shell_back(0) == ATTR_ERROR)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	g_glob.command_line.interrupted = WIFSIGNALED(res_save);
	return (SUCCESS);
}
