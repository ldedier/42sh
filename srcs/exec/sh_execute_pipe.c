/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/09 17:53:57 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static pid_t 		fork_for_pipe(int *pds, t_list *last_cmd)
{
	pid_t 	child;

	(void)pds;
	(void)last_cmd;
	if (last_cmd)
	{
		if (pipe(pds))
		{
			sh_perror(SH_ERR1_PIPE, "execution commande pipe");
			return (-1);
		}
	}
	if ((child = fork()) < 0)
	{
		sh_perror(SH_ERR1_FORK, "execution fork for pipe");
		return (-1);
	}
	return (child);
}

static int 		child_exec(
	int *pds_prev, int *pds, t_ast_node *node_to_execute, t_context *context)
{
	int 		ret;

	ret = 0;
	if (pds_prev)
	{
		if ((ret = dup2(pds_prev[INPUT], STDIN_FILENO)) >= 0)
			close(pds_prev[OUTPUT]);
	}
	if (ret >= 0 && pds)
	{
		if ((ret = dup2(pds[OUTPUT], STDOUT_FILENO)) >= 0)
			close(pds[INPUT]);
	}
	if (ret < 0)
	{
		sh_reset_redirection(&context->redirections);
		sh_free_all(context->shell);
		exit(ERROR);
	}
	ret = sh_traverse_simple_command(node_to_execute, context);
	if (pds)
		close(pds[OUTPUT]);
	if (pds_prev)
		close(pds_prev[INPUT]);
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	return (ret);
}

/*
 * loop_pipe_exec
 * This function look over the t_list pipe_sequece (grammar)
 * fork and execute in the father process the current pipe sequence.
*/
static int 		loop_pipe_exec(
	pid_t *next_proc, int *pds_prev, t_list *lst_sequences, t_context *context)
{
	pid_t		child;
	int			pds[2];
	int 		ret;
	t_ast_node	*curr_sequence;

	curr_sequence = lst_sequences->content;
	if (lst_sequences->next == NULL)
	{
		if ((child = fork_for_pipe(pds, lst_sequences->next)) < 0)
			return (ERROR);
		else if (child)
		{
			*next_proc = child;
			return (SUCCESS);
		}
		exit(child_exec(pds_prev, NULL, curr_sequence, context));
	}
	else if (((t_ast_node *)(lst_sequences->content))->symbol->id
		== sh_index(LEX_TOK_PIPE))
		return (loop_pipe_exec(next_proc, pds_prev, lst_sequences->next, context));
	else
	{
		if (pipe(pds))
		{
			sh_perror(SH_ERR1_PIPE, "execution commande pipe");
			return (-1);
		}
		if ((ret = loop_pipe_exec(next_proc, pds, lst_sequences->next, context)) != SUCCESS)
			return (ret);
		if ((child = fork_for_pipe(pds, lst_sequences->next)) < 0)
			return (ERROR);
		else if (!child)
		{
			child_exec(pds_prev, pds, curr_sequence, context);
			waitpid(*next_proc, &ret, 0);
			sh_env_update_ret_value_wait_result(context, ret);//need to do this only with the last cmd
			exit(ret);
		}
		else
		{
			waitpid(child, &ret, 0);// this is only for the last cmd that don't work
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

/*
 * sh_exec_pipe_sequence
 * This the execution file of pipe.
 * We scan the list of pipeline and apply a pipe
 * (fork, pipe, dup2...) for each pipe separator we find.
 *
 * Father process and the last child call the next level on the ast
 * sh_traverse_simple_command
*/
int				sh_execute_pipe(t_ast_node *node,
		t_context *context)
{
	t_list		*lst_psequences;
	int 		ret;
	pid_t		next_proc;

	next_proc = 0;
	lst_psequences = node->children;
	ret = loop_pipe_exec(&next_proc, NULL, lst_psequences, context);
	return (ret);
}
