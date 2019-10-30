/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:41:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/30 17:11:09 by jdugoudr         ###   ########.fr       */
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
** close_one_pipe
** In the shell process we need to close pipe
** just after fork the associate command
*/

void		close_one_pipe(int curr, t_pipe *pipes)
{
	if (curr < pipes->nb_pipe)
	{
		close(pipes->tab_pds[curr][INPUT]);
		close(pipes->tab_pds[curr][OUTPUT]);
	}
}

pid_t 		fork_for_pipe(void)
{
	pid_t 	child;
	int		ret;

	/*
	** jdugoudr : comme ca le deuxieme fork fail
	** Et ca crash, si le premier fork fail, ca marche bien.
	*/
	// static int	i = 0;
	// if (i == 1)
	// {
	// 	sh_perror(SH_ERR1_FORK, "execution fork for pipe");
	// 	return (-1);
	// }
	/*
	** remet ce qui est avant pour faire fork fail
	*/
	if ((child = fork()) < 0)
	{
		sh_perror(SH_ERR1_FORK, "execution fork for pipe");
		return (-1);
	}
	// i++; // remete ca aussi
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
** creat_all_pipe
** If we have a intern problems like can't fork,
** we have to wait for created process.
*/

int		create_all_pipe(int nb_pipe, t_pipe *pipes, t_list *lst_psequences,
			t_context *context)
{
	int	pds[2];
	int	ret;
	int	i;

	i = -1;
	if (nb_pipe == -1)
	{
		ret = loop_pipe_exec(0, pipes, lst_psequences, context);
		ft_dprintf(g_term_fd, "loop pipe exec ret: %d\n", ret);
		if (ret != SUCCESS)
		{
			ft_dprintf(g_term_fd, "waiting for unfinished children after fork fails\n");
			while (++i < pipes->nb_cmd)
			{
				if (pipes->tab_pid[i] != 0)
					waitpid(pipes->tab_pid[i], &ret, WNOHANG);
			}
			return (ret);
		}
		return (ret);
	}
	if (pipe(pds))
	{
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (-1);	//Pourquoi -1 ici?
	}
	pipes->tab_pds[nb_pipe] = pds;
	return (create_all_pipe(nb_pipe - 1, pipes, lst_psequences, context));
}

/*
** close_all_pipe
** close all pipe for shell process if
** needed if an error appear during fork
*/
void		close_all_pipe(t_pipe *pipes)
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
