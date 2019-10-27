/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 08:21:00 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/27 12:21:49 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t 		fork_for_pipe(void)
{
	pid_t 	child;
	int		ret;

	if ((child = fork()) < 0)
	{
		sh_perror(SH_ERR1_FORK, "execution fork for pipe");
		return (-1);
	}
	if (child == 0)
	{
		if (g_job_ctrl->interactive)
		{
			if ((ret = set_pgid_child(child)) != SUCCESS)
				return (ret);
		}
	}
	else
	{
		if (g_job_ctrl->interactive && set_pgid_parent(child) != SUCCESS)
			return (-1);
	}
	return (child);
}

/*
** child_exec
** Apply pipe redirection and call next level on ast, simple_command
*/

static int		child_exec(
		int curr_cmd, t_pipe *pipes, t_ast_node *to_execute, t_context *context)
{
	int	ret;

	ret = 0;
	close_all_pipe_but_one(pipes->nb_pipe, curr_cmd, pipes->tab_pds);
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
	}
	/*ft_dprintf(2, "on close_and_free\n");*/
	g_job_ctrl->interactive = 1;
	close_and_free(curr_cmd, pipes, context);
	if (ret == SUCCESS)
		return (context->shell->ret_value);
	return (ret);
}

/*
** loop_pipe_exec
** This function look over the t_list pipe_sequece (grammar)
** fork and execute in the child process the current pipe sequence.
*/

static int		loop_pipe_exec(
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
** creat_all_pipe
** If we have a intern problems like can't fork,
** we have to wait for created process.
*/

static int		create_all_pipe(
		int nb_pipe, t_pipe *pipes, t_list *lst_psequences, t_context *context)
{
	int	pds[2];
	int	ret;
	int	i;

	i = 0;
	if (nb_pipe == -1)
	{
		ret = loop_pipe_exec(0, pipes, lst_psequences, context);
		if (ret != SUCCESS)
		{
			while (i < pipes->nb_cmd)
				waitpid(pipes->tab_pid[i++], &ret, 0);
			return (ERROR);
		}
		return (ret);
	}
	if (pipe(pds))
	{
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (-1);
	}
	pipes->tab_pds[nb_pipe] = pds;
	return (create_all_pipe(nb_pipe - 1, pipes, lst_psequences, context));
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


int				sh_execute_pipe(t_ast_node *node, t_context *context)
{
	int			ret;
	int			i;
	t_pipe		pipes;

	i = 0;
	ret = ERROR;
	pipes.nb_pipe = ft_lstlen(node->children) / 2;
	pipes.nb_cmd = pipes.nb_pipe + 1;
	pipes.tab_pid = NULL;
	pipes.tab_pds = NULL;
	if ((pipes.tab_pds = malloc(pipes.nb_pipe * sizeof(int *))) == NULL
			|| (pipes.tab_pid = malloc(pipes.nb_cmd * sizeof(pid_t))) == NULL)
		sh_env_update_ret_value(context->shell, ret);
	else if (!create_all_pipe(pipes.nb_pipe - 1, &pipes, node->children, context))
	{
		if (g_job_ctrl->interactive)
		{
			if (g_job_ctrl->curr_job->foreground)
				if (sh_pre_execution() != SUCCESS)
					return (FAILURE);
			if (g_job_ctrl->curr_job->foreground == 0)
					ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
			else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
				return (FAILURE);
			sh_env_update_ret_value_wait_result(context, ret);
		}
		else
		{
			// ft_dprintf(g_term_fd, "WFLAGS: %d\n", context->wflags);
			while (i++ < pipes.nb_cmd)
				if (waitpid(-1, &ret, context->wflags) == pipes.tab_pid[pipes.nb_cmd - 1])
					sh_env_update_ret_value_wait_result(context, ret);
		}
	}
	else
		sh_env_update_ret_value(context->shell, ret);
	free(pipes.tab_pds);
	free(pipes.tab_pid);
	return (SUCCESS);
}