/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:10:38 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/17 00:38:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

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

	pid = waitpid(- j->pgid, &status, WUNTRACED);
	while (!job_check_changes(pid, status) && !job_is_stopped(j))
			// && !job_is_completed(j))
		pid = waitpid(- j->pgid, &status, WUNTRACED);
	// ft_dprintf(g_term_fd, "%sJob wait returned: %d%s\n", COLOR_PINK, status, EOC);
	*ret = status;
}