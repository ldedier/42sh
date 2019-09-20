/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:05:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 01:14:48 by mdaoud           ###   ########.fr       */
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

	j = g_job_ctrl->first_job;

	job_check_updates_nohang();

}