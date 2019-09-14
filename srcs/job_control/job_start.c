/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:16:21 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/15 00:02:41 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "sh_21.h"

int		job_start(t_job *j, int foreground)
{
	t_process	*p;
	pid_t		pid;
	int			status;

	p = j->first_process;
	while (p != NULL)
	{
		/* Fork the child processes.  */
		pid = fork ();
		if (pid == 0)
		/* This is the child process.  */
		j_process_start(p, j->pgid, foreground);	//To be implemented
		else if (pid < 0)
		{
			/* The fork failed.  */
			perror ("fork");
			exit (1);
		}
		else
		{
			/* This is the parent process.  */
			p->pid = pid;
			if (g_job_control->shell_is_interactive)
			{
			if (!j->pgid)
				j->pgid = pid;
			setpgid (pid, j->pgid);
			waitpid(pid, &status, 0);

			}
		}
		p = p->next;
	}

	// format_job_info (j, "launched");	// To be implemented

	// if (!g_job_control->shell_is_interactive)
	// 	wait_for_job (j);
	// else if (foreground)
	// 	put_job_in_foreground (j, 0);
	// else
	// 	put_job_in_background (j, 0);
}
