/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_check_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:54:07 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 00:06:55 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"
#include "errno.h"

int			process_check_status(pid_t pid, int status)
{
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		/* Update the record for the process.  */
		for (j = g_job_ctrl->first_job; j; j = j->next)
			for (p = j->first_process; p; p = p->next)
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
							ft_dprintf (STDERR_FILENO, "%d: Terminated by signal %d.\n",
								(int) pid, WTERMSIG (p->status));
					}
					return (0);
				}
		ft_dprintf (STDERR_FILENO, "No child process %d.\n", pid);
		return (-1);
	}

	else if (pid == 0 || errno == ECHILD)	//Carefull
	/* No processes ready to report.  */
		return (-1);
	else
	{
		/* Other weird errors.  */
		perror ("waitpid");
		return (-1);
	}
}