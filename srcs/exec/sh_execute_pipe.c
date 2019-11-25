/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:21:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/25 10:26:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** child_exec
** Apply pipe redirection and call next level on ast, simple_command
*/

static int	child_exec(
		int curr_cmd, t_pipe *pipes, t_ast_node *to_execute, t_context *context)
{
	int	ret;

	ret = 0;
	close_all_pipes_but_one(pipes->nb_pipe, curr_cmd, pipes->tab_pds);
	if (curr_cmd > 0)
		ret = dup2(pipes->tab_pds[curr_cmd - 1][INPUT], STDIN_FILENO);
	if (ret >= 0 && curr_cmd < pipes->nb_pipe)
		ret = dup2(pipes->tab_pds[curr_cmd][OUTPUT], STDOUT_FILENO);
	if (ret < 0)
		ret = ERROR;
	else
		ret = SUCCESS;
	if (ret == SUCCESS)
	{
		g_job_ctrl->interactive = 0;
		ret = sh_traverse_command(to_execute, context);
		if (ret == SUCCESS)
			ret = context->shell->ret_value;
	}
	g_job_ctrl->interactive = 1;
	close_pipes_and_free(curr_cmd, pipes, context);
	return (ret);
}

static int	pipe_wait(t_context *context, t_pipe *pipes)
{
	int	ret;
	int	i;

	if (g_job_ctrl->interactive)
	{
		if (g_job_ctrl->curr_job->foreground)
			if (sh_pre_execution() != SUCCESS)
				return (FAILURE);
		if (g_job_ctrl->curr_job->foreground == 0)
		{
			if ((ret = job_put_in_bg(g_job_ctrl->curr_job)) != SUCCESS)
				return (FAILURE);
		}
		else if ((job_put_in_fg(g_job_ctrl->curr_job, 0, &ret)) != SUCCESS)
			return (FAILURE);
		sh_env_update_ret_value_wait_result(context, ret);
		return (SUCCESS);
	}
	i = 0;
	while (i++ < pipes->nb_cmd)
		if (waitpid(-1, &ret, context->wflags) ==
				pipes->tab_pid[pipes->nb_cmd - 1])
			sh_env_update_ret_value_wait_result(context, ret);
	return (SUCCESS);
}

/*
** loop_pipe_exec
** This function look over the t_list pipe_sequece (grammar)
** fork and execute in the child process the current pipe sequence.
*/

int			loop_pipe_exec(
	int curr_cmd, t_pipe *pipes, t_list *lst_sequences, t_context *context)
{
	int			ret;
	t_ast_node	*curr_sequence;

	curr_sequence = lst_sequences->content;
	if (curr_cmd == pipes->nb_cmd - 1 && lst_sequences->next == NULL)
	{
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (pipes->tab_pid[curr_cmd] == 0)
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
	}
	else if (curr_sequence->symbol->id == sh_index(LEX_TOK_PIPE))
		return (loop_pipe_exec(curr_cmd, pipes, lst_sequences->next, context));
	else
	{
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (pipes->tab_pid[curr_cmd] == 0)
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
		if ((ret = loop_pipe_exec(
						curr_cmd + 1, pipes, lst_sequences->next, context)))
			return (ret);
	}
	close_one_pipe(curr_cmd, pipes);
	return (SUCCESS);
}

/*
** sh_execute_pipe
** This the execution file of pipe.
**
** The shell call all cmd of the pipe sequence and stock
** each of them and all pipe in a structure t_pipe.
** After fork for all cmd we wait for the end of all of them.
**
** Return :
** SUCCESS if no problems appeared
** ERROR otherwise
*/

int			sh_execute_pipe(t_ast_node *node, t_context *context)
{
	int			ret;
	t_pipe		pipes;

	pipes.nb_pipe = ft_lstlen(node->children) / 2;
	pipes.nb_cmd = pipes.nb_pipe + 1;
	pipes.tab_pid = NULL;
	if ((pipes.tab_pds = malloc(pipes.nb_pipe * sizeof(int *))) == NULL
			|| (pipes.tab_pid = malloc(pipes.nb_cmd * sizeof(pid_t))) == NULL)
		ret = FAILURE;
	else
	{
		ret = -1;
		while (++ret < pipes.nb_cmd)
			pipes.tab_pid[ret] = 0;
		if (!(ret = create_all_pipe(pipes.nb_pipe - 1,
					&pipes, node->children, context)))
			ret = pipe_wait(context, &pipes);
		else
			pipe_fail_protocol(context, ret);
	}
	free(pipes.tab_pds);
	free(pipes.tab_pid);
	return (ret);
}
