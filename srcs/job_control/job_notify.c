/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:05:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/11 21:10:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static void		job_check_updates_nohang(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(ANY_CHILD_PROCESS, &status, WUNTRACED | WNOHANG);
	while (!job_check_changes(pid, status))
		pid = waitpid(ANY_CHILD_PROCESS, &status, WUNTRACED | WNOHANG);
}

static void		report_completed_job_status(t_job *j)
{
	if (j->signal_num == SIGHUP)
		job_print_status(j, "Hangup");
	else if (j->signal_num == SIGINT)
		job_print_status(j, "Interrupt");
	else if (j->signal_num == SIGQUIT)
		job_print_status(j, "Quit");
	else
		job_print_status(j, "Done");
	j->notified = 1;
}

/*
** When we recieve a SIGCHLD from a process in the background,
**	We call waitpid with the flag "WNOHANG" that will return the pid of
**	the process that has changed status.
** We then check all of our jobs and their processes to see which process that pid
**	coressponds to, then we update the status of that process and job,
**	and notify the user of any notable changes.
*/

void			job_notify(void)
{
	t_job	*j;
	t_job	*j_next;
	t_job	*tmp;

	job_check_updates_nohang();
	j = g_job_ctrl->first_job;
	tmp = NULL;
	while (j != NULL)
	{
		j_next = j->next;
		// If the job is completed, report to user and remove the job from the list.
		if (job_is_completed(j))
		{
			g_job_ctrl->job_num[j->number] = 0;
			if (j->foreground == 0)
				report_completed_job_status(j);
			if (tmp)
				tmp->next = j_next;
			else
				g_job_ctrl->first_job = j_next;
			if (g_job_ctrl->curr_job == j)
				g_job_ctrl->curr_job = NULL;
			job_free(j);
		}
		// If the job has stopped (but not completed), report to the user (only once)
		else if (job_is_stopped(j) && !j->notified)
		{
			job_print_status(j, "Stopped");
			j->notified = 1;
			tmp = j;
		}
		else
			tmp = j;
		j = j_next;
	}
	// render_command_line(&g_glob.command_line, 0, 1);
}
