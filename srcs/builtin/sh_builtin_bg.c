/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/01 02:08:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"

static void		mark_job_as_running (t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p != NULL)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

int			sh_builtin_bg(t_context *context)
{
	t_job	*active_job;
	int		res;

	active_job = get_active_job();
	if (active_job == NULL)
		return (ERROR);
	mark_job_as_running(active_job);
	active_job->foreground = 0;
	if (kill(- active_job->pgid, SIGCONT) < 0)
	{
		ft_dprintf(STDERR_FILENO, "kill SIGCONT\n");
		return (ERROR);
	}
	job_print_status(active_job, "continued");
	return(SUCCESS);
}
