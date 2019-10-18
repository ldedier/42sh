/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/17 09:05:45 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


/*
** child_exec
** Apply pipe redirection and call next level on ast, simple_command
*/

static int 		child_exec(
	int curr_cmd, t_pipe *pipes, t_ast_node *node_to_execute, t_context *context)
{
	int 		ret;

	ret = 0;
	close_all_pipe_but_one(pipes->nb_pipe, curr_cmd, pipes->tab_pds);
	if (curr_cmd > 0)
		ret = dup2(pipes->tab_pds[curr_cmd - 1][INPUT], STDIN_FILENO);
	if (ret >= 0 && pipes->nb_pipe > curr_cmd)
		ret = dup2(pipes->tab_pds[curr_cmd][OUTPUT], STDOUT_FILENO);
	if (ret < 0)
		ret = ERROR;
	else
		ret = SUCCESS;
	if (ret == SUCCESS)
		ret = sh_traverse_simple_command(node_to_execute, context);
	close_and_free(curr_cmd, pipes, context);
	return (ret);
}

/*
** loop_pipe_exec
** This function look over the t_list pipe_sequece (grammar)
** fork and execute in the child process the current pipe sequence.
*/

static int 		loop_pipe_exec(
	int curr_cmd, t_pipe *pipes, t_list *lst_sequences, t_context *context)
{
	int 		ret;
	t_ast_node	*curr_sequence;

	curr_sequence = lst_sequences->content;
	if (curr_cmd == pipes->nb_cmd - 1 && lst_sequences->next == NULL)
	{
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (!pipes->tab_pid[curr_cmd])
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
	}
	else if (curr_sequence->symbol->id == sh_index(LEX_TOK_PIPE))
		return (loop_pipe_exec(curr_cmd, pipes, lst_sequences->next, context));
	else
	{
		if ((ret = loop_pipe_exec(
						curr_cmd + 1, pipes, lst_sequences->next, context)))
			return (ret);
		if ((pipes->tab_pid[curr_cmd] = fork_for_pipe()) < 0)
			return (ERROR);
		else if (!pipes->tab_pid[curr_cmd])
			exit(child_exec(curr_cmd, pipes, curr_sequence, context));
	}
	return (SUCCESS);
}

static int		create_all_pipe(int nb_pipe, t_pipe *pipes,
					t_list *lst_psequences, t_context *context)
{
	int	pds[2];
	int	ret;

	if (nb_pipe == -1)
	{
		ret = loop_pipe_exec(0, pipes, lst_psequences, context);
		close_all_pipe(pipes->nb_pipe - 1, pipes->tab_pds);
		return (ret);
	}
	if (pipe(pds))//checker si pas d'erreur au milieu d'une pipe sequence
	{
		// CHECK FOR THE NEED FOR FREE
		free(pipes->tab_pds);
		free(pipes->tab_pid);
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (ERROR);
	}
	pipes->tab_pds[nb_pipe] = pds;
	return (create_all_pipe(nb_pipe - 1, pipes, lst_psequences, context));
}

/*
** If we are in an interactive shell, we treat the pipe as a job.
** If we are in an non-interactive shell,
**	or if we already forked for a background and or, we just wait with waitpid.
*/

static int		sh_pipe_wait(t_context *context, t_pipe *pipes)
{
	int		ret;

	// 12 means AND_OR_NODE(4) & BG_NODE(8), too laze to write the whole thing
	if (g_job_ctrl->interactive && (context->cmd_type & 12) != 12)
	{
		if (g_job_ctrl->curr_job->foreground == 0)
				ret = job_put_in_bg(g_job_ctrl->curr_job, 0);
		else if (job_put_in_fg(g_job_ctrl->curr_job, 0, &ret) != SUCCESS)
			return (FAILURE);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		sh_env_update_ret_value_wait_result(context, ret);
		// ft_dprintf(g_term_fd, "%sRet in pipe: %#X (%d)\n%s",BLUE, context->shell->ret_value, context->shell->ret_value, EOC);
	}
	else
	{
		if (--pipes->nb_cmd >= 0)
			waitpid(pipes->tab_pid[pipes->nb_cmd], &ret, 0);
		sh_env_update_ret_value_wait_result(context, ret);
		while (--pipes->nb_cmd >= 0)
			waitpid(pipes->tab_pid[pipes->nb_cmd], &ret, 0);
		// ft_dprintf(g_term_fd, "%sRet in pipe: %#X (%d)\n%s",CYAN, context->shell->ret_value, context->shell->ret_value, EOC);
	}
	return (SUCCESS);
}
/*
** sh_execute_pipe
** This the execution file of pipe.
**
** The shell call all cmd of the pipe sequence and stock
** each of them and all pipe in a structure t_pipe.
** After fork for all cmd we wait for the end of all of them.
*/
int				sh_execute_pipe(t_ast_node *node, t_context *context)
{
	t_list		*lst_psequences;
	t_pipe		pipes;

	if ((sh_pre_exec_pipe(node, &lst_psequences, &pipes))!= SUCCESS)
		return (FAILURE);
	if (g_job_ctrl->interactive && g_job_ctrl->curr_job->foreground)
		if (sh_pre_execution() != SUCCESS)
		{
			free(pipes.tab_pds);
			free(pipes.tab_pid);
			return (FAILURE);
		}
	if (!create_all_pipe(pipes.nb_pipe - 1, &pipes, lst_psequences, context))
	{
		if (sh_pipe_wait (context, &pipes) != SUCCESS)
		{
			free(pipes.tab_pds);
			free(pipes.tab_pid);
			return (FAILURE);
		}
	}
	free(pipes.tab_pds);
	free(pipes.tab_pid);
	return (SUCCESS);
}
