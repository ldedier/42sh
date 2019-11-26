/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_close_tools.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:37:05 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/26 07:52:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** close_all_pipe_but_one
** As we create pipe in shell process, all child process
** have a reference to all the pipe.
** Before execution we close all unused pipe.
*/

void	close_all_pipes_but_one(int nb_pipe, int curr_cmd, int **tab_pds)
{
	int	i;

	i = 0;
	while (i < nb_pipe)
	{
		if (i == curr_cmd)
			close(tab_pds[i][INPUT]);
		else if (i == curr_cmd - 1)
			close(tab_pds[i][OUTPUT]);
		else
		{
			close(tab_pds[i][OUTPUT]);
			close(tab_pds[i][INPUT]);
		}
		i++;
	}
}

/*
** close_and_free
** After the execution, we have to close used pipe, to send a signal
** at the other side of the pipe
** free to not have any leaks
*/

void	close_pipes_and_free(int curr_cmd, t_pipe *pipes, t_context *context)
{
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	free_execution_tools(&context->shell->exec->tokens,
		&context->shell->exec->ast_root, &context->shell->exec->cst_root);
	if (pipes->nb_pipe > curr_cmd)
	{
		close(pipes->tab_pds[curr_cmd][OUTPUT]);
		close(STDOUT_FILENO);
	}
	if (curr_cmd > 0)
	{
		close(pipes->tab_pds[curr_cmd - 1][INPUT]);
		close(STDIN_FILENO);
	}
	free(pipes->tab_pds);
	free(pipes->tab_pid);
}

/*
** close_one_pipe
** In the shell process we need to close pipe
** just after fork the associate command
*/

void	close_one_pipe(int curr, t_pipe *pipes)
{
	if (curr < pipes->nb_pipe)
	{
		close(pipes->tab_pds[curr][INPUT]);
		close(pipes->tab_pds[curr][OUTPUT]);
	}
}

/*
** close_all_pipe
** close all pipe for shell process if
** needed if an error appear during fork
*/

void	close_all_pipes(t_pipe *pipes)
{
	int		i;

	i = 0;
	while (i < pipes->nb_pipe)
	{
		close(pipes->tab_pds[i][INPUT]);
		close(pipes->tab_pds[i][OUTPUT]);
		i++;
	}
}
