/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/18 11:44:29 by mdaoud           ###   ########.fr       */
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

	if (g_job_ctrl->first_job == g_job_ctrl->curr_job)
	{
		sh_perror("bg: current", "no such job");
		return (NULL);
	}
	j = g_job_ctrl->first_job;
	it = NULL;
	while (j->next != NULL)
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
	t_job	*j;

	(void)context;
	j = get_active_job();
	if (j == NULL)
		return (ERROR);
	ft_dprintf(g_term_fd, "%sActive job: [%d] \"%s\"%s\n", YELLOW, j->number, j->command, EOC);
	if (kill(- j->pgid, SIGCONT) < 0)
	{
		ft_dprintf(STDERR_FILENO, "kill SIGCONT\n");
		return (ERROR);
	}
	j->foreground = 0;
	mark_job_as_running(j);
	// job_print_status(j, "Continued");
	ft_dprintf(g_term_fd, "[%d]  %s &\n",
		j->number, j->command);
	return (SUCCESS);
}

