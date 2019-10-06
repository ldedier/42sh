/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/06 02:48:27 by mdaoud           ###   ########.fr       */
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

static t_job	*get_active_job(void)
{
	t_job	*j;
	t_job	*it;
	t_job	*prev;

	if (g_job_ctrl->first_job == NULL)
	{
		sh_perror("bg: current", "no such job");
		return (NULL);
	}
	j = g_job_ctrl->first_job;
	it = NULL;
	while (j != NULL)
	{
		prev = j;
		if (job_is_stopped(j))
			it = j;
		j = j->next;
	}
	if (it == NULL)
	{
		sh_perror("bg", NULL);
		ft_dprintf(2, "job [%d] already running in background\n", prev->number);
		return (NULL);
	}
	return (it);
}

int				sh_builtin_bg(t_context *context)
{
	t_job	*active_job;
	int		res;

	active_job = get_active_job();
	if (active_job == NULL)
		return (ERROR);
	if (kill(- active_job->pgid, SIGCONT) < 0)
	{
		ft_dprintf(STDERR_FILENO, "kill SIGCONT\n");
		return (ERROR);
	}
	active_job->foreground = 0;
	mark_job_as_running(active_job);
	// job_print_status(active_job, "Continued");
	ft_dprintf(g_job_ctrl->term_fd, "[%d]  %s &\n",
		active_job->number, active_job->command);
	return (SUCCESS);
}

