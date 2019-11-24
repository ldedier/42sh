/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:10:38 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:16:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static pid_t	get_last_pid(t_job *j)
{
	t_process	*p;

	if (j == NULL || j->first_process == NULL)
		return (-1);
	p = j->first_process;
	while (p->next != NULL)
		p = p->next;
	return (p->pid);
}

/*
** Wait for any process in the job <j>
** Setting the waitpid first argument to -pgid means wait for any process -
** With the pgid <pgid> (man waitpid).
** waitpid will return the pid of the process that changed status.
** After that we need to check in our job structure,
**	which job has the process with pid <pid> in it, then update it.
** We do that until there are no process that have changed status.
*/

void			job_wait(t_job *j, int *ret)
{
	int		status;
	pid_t	pid;
	pid_t	last_pid;

	last_pid = get_last_pid(j);
	pid = waitpid(-j->pgid, &status, WUNTRACED);
	if (pid == last_pid)
		*ret = status;
	while (!job_check_changes(pid, status)
		&& !job_is_stopped(j) && !job_is_completed(j))
	{
		pid = waitpid(-j->pgid, &status, WUNTRACED);
		if (pid == last_pid)
			*ret = status;
	}
}
