/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_process_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:37:47 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 15:51:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int		j_process_start(t_process *p, pid_t pgid, int foreground)
{
	pid_t pid;

	if (g_job_ctrl->shell_is_interactive)
	{
		/* Put the process into the process group and give the process group
		the terminal, if appropriate.
		This has to be done both by the shell and in the individual
		child processes because of potential race conditions. */
		pid = getpid ();
		if (pgid == 0)
			pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (g_job_ctrl->term_fd, pgid);

		/* Set the handling for job control signals back to the default. */
		signal (SIGINT, SIG_DFL);
		signal (SIGQUIT, SIG_DFL);
		signal (SIGTSTP, SIG_DFL);
		signal (SIGTTIN, SIG_DFL);
		signal (SIGTTOU, SIG_DFL);
		signal (SIGCHLD, SIG_DFL);
	}
	/* Exec the new process. Make sure we exit. */
	execvp (p->argv[0], p->argv);
	perror ("execvp");
	exit (1);
}