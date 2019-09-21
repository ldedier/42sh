/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:05:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 16:55:09 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void		job_check_updates_nohang(void)
{
	int		status;
	pid_t	pid;
	t_job	*j;

	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		pid = waitpid(-1, &status, WUNTRACED | WNOHANG);
		while (!job_check_process_changes(pid, status) && !job_is_stopped(j)
				&& !job_is_completed(j))
			pid = waitpid(-1, &status, WUNTRACED);
		j = j->next;
	}
}


void			job_notify(void)
{
	t_job	*j;
	t_job	*j_next;
	t_job	*tmp;


	// job_check_updates_nohang();
	j = g_job_ctrl->first_job;
	tmp = NULL;
	while (j != NULL)
	{
		j_next = j->next;

		if (job_is_completed(j))
		{
			if (j->foreground == 0)
				job_print_status(j, "completed");
			if (tmp)
				tmp->next = j_next;
			else
				g_job_ctrl->first_job = j_next;
			// job_free(j);
			g_job_ctrl->job_num[j->number] = 0;
		}
		/* Notify the user about stopped jobs,
		marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified)
		{
			job_print_status(j, "stopped");
			j->notified = 1;
			tmp = j;
		}

		/* Don’t say anything about jobs that are still running.  */
		else
			tmp = j;
		j = j->next;
	}
}