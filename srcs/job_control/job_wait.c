/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:10:38 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/17 02:24:01 by mdaoud           ###   ########.fr       */
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


void		job_wait(t_job *j, int *ret)
{
	int		status;
	pid_t	pid;
	pid_t	last_pid;

	last_pid = get_last_pid(j);
	pid = waitpid(- j->pgid, &status, WUNTRACED);
	if (pid == last_pid)
		*ret = status;
	// ft_dprintf(g_term_fd, "%spid: <%d>%s\n",COL_B_MAGENTA, pid, EOC);
	// ft_dprintf(g_term_fd, "%sRet from job wait: %#X (%d)%s\n",COL_B_MAGENTA, status,status, EOC);
	// ft_dprintf(g_term_fd, "%s%s pid in job%s\n", COL_B_MAGENTA, (pid == last_pid ? "LAST" : "NOT LAST"), EOC);
	while (!job_check_changes(pid, status) && !job_is_stopped(j) && !job_is_completed(j))
	{
		pid = waitpid(- j->pgid, &status, WUNTRACED);
		if (pid == last_pid)
			*ret = status;
		// ft_dprintf(g_term_fd, "%spid: <%d>%s\n",COL_B_MAGENTA, pid, EOC);
		// ft_dprintf(g_term_fd, "%sRet from job wait: %#X (%d)%s\n",COL_B_MAGENTA, status,status, EOC);
		// ft_dprintf(g_term_fd, "%s%s pid in job%s\n", COL_B_MAGENTA, (pid == last_pid ? "LAST" : "NOT LAST"), EOC);
	}
	// ft_dprintf(g_term_fd, "%sJob wait returned: %d%s\n", COLOR_PINK, status, EOC);
}