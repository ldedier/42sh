/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/16 03:13:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** When we put a job in the background,
**	the pid of the last process in that wil be printed.
*/

// pid_t		get_last_process_pid(t_job *j)
// {
// 	t_process	*p;

// 	if (j == NULL)
// 		return (0);
// 	p = j->first_process;
// 	if (p == NULL)
// 		return (0);
// 	while (p != NULL && p->next != NULL)
// 		p = p->next;
// 	return (p->pid);
// }

/*
** Putting the job in background only means printing the message on the terminal.
** Since it's in the background we don't have to wait for it.
** cont: if the job was previously stopped and we want to continue it.
*/

int			job_put_in_bg(t_job *j, int cont)
{
	t_process	*p;

	j->foreground = 0;
	j->notified = 1;
	if (cont && (kill (- j->pgid, SIGCONT)) < 0)
		return (jobs_error_free("job_put_in_bg", "kill", 0, ERROR));
	ft_dprintf(g_term_fd, "[%d]  ", j->number);
	p = j->first_process;
	while (p != NULL)
	{
		ft_dprintf(g_term_fd, "%d ", p->pid);
		p = p->next;
	}
	// int ret;
	// waitpid(- j->pgid, &ret, WNOHANG);
	ft_dprintf(g_term_fd, "\n");
	return (SUCCESS);
}