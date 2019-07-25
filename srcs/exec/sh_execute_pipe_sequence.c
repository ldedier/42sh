/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_sequence.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 10:45:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/26 01:15:42 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

extern pid_t g_parent;

static void		sh_execute_pipe_sequence_close_pipes_list(t_list *contexts)
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

static int		sh_execute_pipe_sequence_exec_forks(t_list *contexts)
{
	t_list		*ptr;
	t_context	*context_iter;

	ptr = contexts;
	while (ptr != NULL)
	{
		context_iter = (t_context *)ptr->content;
		if ((context_iter->pid = fork()) == -1)
		{
			sh_execute_pipe_sequence_close_pipes_list(contexts);
			return (FAILURE);
		}
		if (context_iter->pid == 0)
			sh_execute_child(context_iter, contexts);
		else
		{
			g_parent = context_iter->pid;
			ptr = ptr->next;
		}
	}
	return (SUCCESS);
}

static void		sh_execute_pipe_sequence_waits(t_context *context,
	int *res_save)
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
}

int				sh_execute_pipe_sequence(t_context *context, t_list *contexts)
{
	int			res_save;

	if (isatty(0) && sh_reset_shell(0) == -1)
	{
		sh_execute_pipe_sequence_close_pipes_list(contexts);
		return (FAILURE);
	}
	if (sh_execute_pipe_sequence_exec_forks(contexts) == FAILURE)
		return (FAILURE);
	sh_execute_pipe_sequence_close_pipes_list(contexts);
	sh_execute_pipe_sequence_waits(context, &res_save);
	sh_env_update_ret_value_wait_result(context, res_save);
	g_parent = 0;
	if (isatty(0) && tcsetattr(0, TCSADRAIN, context->term) == -1)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	g_glob.command_line.interrupted = WIFSIGNALED(res_save);
	return (SUCCESS);
}
