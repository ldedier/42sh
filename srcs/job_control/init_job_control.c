/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_job_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:24:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 00:43:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

int		init_job_control(t_shell *shell)
{

	g_job_control = malloc(sizeof(t_job_control));
	if (g_job_control == NULL)
	{
		return (FAILURE);
	}
	g_job_control->job_count = 1;
	g_job_control->term_fd = open("/dev/tty", O_WRONLY);
	g_job_control->first_job = NULL;
	g_job_control->current_job = NULL;
	g_job_control->shell_is_interactive = 1;
	if (g_job_control->shell_is_interactive)
	{
		/* Loop until we are in the foreground. */
		// while (tcgetpgrp (g_job_control->term_fd) != (g_job_control->shell_pgid = getpgrp ()))
		// 	kill (- g_job_control->shell_pgid, SIGTTIN);

		/* Ignore interactive and job-control signals. */
		// signal (SIGINT, SIG_IGN);
		// signal (SIGQUIT, SIG_IGN);
		// signal (SIGTSTP, SIG_IGN);
		// signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		// signal (SIGCHLD, SIG_IGN);

		/* Put ourselves in our own process group. */
		g_job_control->shell_pgid = getpid ();
		if (setpgid (g_job_control->shell_pgid, g_job_control->shell_pgid) < 0)
		{
			ft_dprintf(STDERR_FILENO, "Couldn't put the shell in its own process group");
			return (FAILURE);
		}
		/* Grab control of the terminal.  */
		tcsetpgrp(g_job_control->term_fd, g_job_control->shell_pgid);
	}
	return (SUCCESS);
}