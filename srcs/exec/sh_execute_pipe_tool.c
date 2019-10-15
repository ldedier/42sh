/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_tool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:41:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/15 15:00:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** close_all_pipe_but_one
** As we create pipe in shell process, all child process
** have a reference to all the pipe.
** Before execution we close all unused pipe.
*/

void		close_all_pipe_but_one(int nb_pipe, int curr_cmd, int **tab_pds)
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

void		close_and_free(int curr_cmd, t_pipe *pipes, t_context *context)
{
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
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
** close_all_pipe
** As we create all pipe in the shell process,
** we need to close all of them, after fork all cmd,
** in the shell process
*/

void		close_all_pipe(int nb_pipe, int **tab_pds)
{
	while (nb_pipe >= 0)
	{
		close(tab_pds[nb_pipe][INPUT]);
		close(tab_pds[nb_pipe][OUTPUT]);
		nb_pipe--;
	}
}
