/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:24:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 16:57:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int		jobs_init(t_shell *shell)
{

	g_job_ctrl = malloc(sizeof(t_job_control));
	if (g_job_ctrl == NULL)
	{
		return (FAILURE);
	}
	g_job_ctrl->job_count = 1;
	g_job_ctrl->term_fd = g_glob.command_line.fd;
	g_job_ctrl->first_job = NULL;
	g_job_ctrl->curr_job = NULL;
	g_job_ctrl->shell_is_interactive = 1;	//	change
	if (g_job_ctrl->shell_is_interactive)
	{
		/* Loop until we are in the foreground. */
		// while (tcgetpgrp (g_job_ctrl->term_fd) != (g_job_ctrl->shell_pgid = getpgrp ()))
		// 	kill (- g_job_ctrl->shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals. */
		// signal (SIGINT, SIG_IGN);
		// signal (SIGQUIT, SIG_IGN);
		// signal (SIGTSTP, SIG_IGN);
		// signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		// signal (SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group. */
		g_job_ctrl->shell_pgid = getpid ();
		if (setpgid (g_job_ctrl->shell_pgid, g_job_ctrl->shell_pgid) < 0)
		{
			ft_dprintf(STDERR_FILENO, "Couldn't put the shell in its own process group");
			return (FAILURE);
		}
		/* Grab control of the terminal.  */
		tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->shell_pgid);
	}
	return (SUCCESS);
}