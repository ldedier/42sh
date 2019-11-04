/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_pipe_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:41:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/31 17:57:27 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

pid_t	fork_for_pipe(void)
{
	pid_t	child;
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
** creat_all_pipe
** If we have a intern problems like can't fork,
** we have to wait for created process.
*/

int		create_all_pipe(int nb_pipe, t_pipe *pipes, t_list *lst_psequences,
			t_context *context)
{
	int	pds[2];
	int	ret;

	if (nb_pipe == -1)
	{
		ret = loop_pipe_exec(0, pipes, lst_psequences, context);
		if (ret != SUCCESS)
		{
			close_all_pipes(pipes);
			kill(-pipes->tab_pid[0], SIGHUP);
			return (ret);
		}
		return (ret);
	}
	if (pipe(pds))
	{
		sh_perror(SH_ERR1_PIPE, "execution commande pipe");
		return (ERROR);
	}
	pipes->tab_pds[nb_pipe] = pds;
	return (create_all_pipe(nb_pipe - 1, pipes, lst_psequences, context));
}

int		pipe_fail_protocol(t_context *context, int ret)
{
	ft_dprintf(g_term_fd, "create_all pipes failed ret: %d\n", ret);
	sh_post_execution();
	if (tcsetpgrp(g_term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		return (sh_perror("tcsetpgrp",
			"Could not give the shell control of the terminal"));
	}
	sh_env_update_ret_value(context->shell, ret);
	return (ret);
}
