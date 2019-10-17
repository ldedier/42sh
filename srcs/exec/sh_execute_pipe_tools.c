/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:20:57 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/17 01:59:41 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** A Function to malloc and initalize the strucutre.
*/

int		sh_pre_exec_pipe(t_ast_node *node, t_list **pseq, t_pipe *pipes)
{
	*pseq = node->children;
	pipes->nb_pipe = ft_lstlen(*pseq) / 2;
	pipes->nb_cmd = pipes->nb_pipe + 1;
	if ((pipes->tab_pds = malloc(pipes->nb_pipe * sizeof(int *))) == NULL)
		return (FAILURE);
	if ((pipes->tab_pid = malloc(pipes->nb_cmd * sizeof(pid_t))) == NULL)
	{
		free(pipes->tab_pds);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
** close_all_pipe_but_one
** As we create pipe in shell process, all child process
** have a reference to all the pipe.
** Before execution we close all unused pipe.
*/

void			close_all_pipe_but_one(int nb_pipe, int curr_cmd, int **tab_pds)
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

pid_t 		fork_for_pipe(void)
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

	// ft_dprintf(g_term_fd, "Fork: pid: %d\tppid: %d\tpgid: %d\n", getpid(), getppid(), getpgid(getpid()));
	return (child);
}