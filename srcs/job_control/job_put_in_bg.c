/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/27 11:47:11 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

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