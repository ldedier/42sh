/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/06 18:26:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t 		fork_for_pipe(int *pds)
{
	pid_t 	child;

	if (pipe(pds))
	{
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (-1);
	}
	if ((child = fork()) < 0)
	{
		sh_perror(SH_ERR1_FORK, "execution fork for pipe");
		return (-1);
	}
	// ft_dprintf(g_job_ctrl->term_fd, "Fork: pid: %d\tppid: %d\tpgid: %d\n", getpid(), getppid(), getpgid(getpid()));
	return (child);
}

static int 		parent_exec(
	pid_t child, int *pds, t_ast_node *node_to_execute, t_context *context)
{
	int 		ret;

	if (dup2(pds[OUTPUT], STDOUT_FILENO) < 0)
		return (STOP_CMD_LINE);
	close(pds[INPUT]);
	sh_traverse_command(node_to_execute, context);
	close(pds[OUTPUT]);
	close(STDOUT_FILENO);
	// ft_dprintf(g_job_ctrl->term_fd, "%s%d waiting for %d%s\n", COLOR_YELLOW, getpid(), child, COLOR_END);
	waitpid(child, &ret, 0);
	return (SH_RET_VALUE_EXIT_STATUS(ret));
}

/*
 * loop_pipe_exec
 * This function look at t_list pipe_sequence (grammar)
 * forks and executes in the parent process the current pipe sequence.
*/
static int 		loop_pipe_exec(
	t_ast_node *curr_sequence, t_list *lst_sequences, t_context *context)
{
	pid_t		child;
	int			pds[2];
	int 		ret;

	if (lst_sequences->next == NULL)
	{
		ret = sh_traverse_command(curr_sequence, context);
		if (ret != SUCCESS)
			return (ret);
		return (context->shell->ret_value);
	}
	else if (((t_ast_node *)(lst_sequences->content))->symbol->id
		!= sh_index(LEX_TOK_PIPE))
		{
		return (loop_pipe_exec(curr_sequence, lst_sequences->next, context));
		}
	else
	{
		if ((child = fork_for_pipe(pds)) < 0)
			return (STOP_CMD_LINE);
		else if (child)
			return (parent_exec(child, pds, curr_sequence, context));
		if (dup2(pds[INPUT], STDIN_FILENO) < 0)
		{
			sh_reset_redirection(&context->redirections);
			sh_free_all(context->shell);
			exit(STOP_CMD_LINE);
		}
		close(pds[OUTPUT]);
		ret = loop_pipe_exec(
			lst_sequences->next->content, lst_sequences->next, context);
		close(pds[INPUT]);
		sh_reset_redirection(&context->redirections);
		sh_free_all(context->shell);
		exit(ret);
	}
}

/*
 * sh_exec_pipe_sequence
 * This the execution file of pipe.
 * We scan the list of pipeline and apply a pipe
 * (fork, pipe, dup2...) for each pipe separator we find.
 *
 * parent process and the last child call the next level on the ast
 * sh_traverse_simple_command
*/
int				sh_execute_pipe(t_ast_node *node,
		t_context *context)
{
	t_list		*lst_psequences;
	int 		ret;

	lst_psequences = node->children;
	ret = loop_pipe_exec(lst_psequences->content, lst_psequences, context);
	return (ret);
}
