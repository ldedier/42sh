/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:22:36 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 00:39:52 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void	job_notify(void)
{
	t_job		*j, *last_job, *next_j;
	t_job		*las;
	t_job		*next;
	t_process	*p;

	/* Update status information for child processes. */
	process_update_status();

	last_job = NULL;
	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		next_j = j->next;

		/* If all processes have completed, tell the user the job has
		completed and delete it from the list of active jobs.  */
		if (job_is_completed(j))
		{
			format_job_info(j, "completed");
			if (last_job)
				last_job->next = next_j;
			else
				g_job_ctrl->first_job = next_j;
			free_job(j);
		}
		/* Notify the user about stopped jobs,
		marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified)
		{
			format_job_info(j, "stopped");
			j->notified = 1;
			last_job = j;
		}

		/* Don’t say anything about jobs that are still running.  */
		else
			last_job = j;
		j = j->next;
	}
}