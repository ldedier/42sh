/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_changes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:46:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/22 00:40:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static void	reset_job_status(t_job *j, const char status_type)
{
	t_process	*p;

	p = j->first_process;
	if (status_type == 's')
	{
		while (p != NULL)
		{
			p->stopped = 0;
			p = p->next;
		}
	}
	else if (status_type == 'c')
	{
		while (p != NULL)
		{
			p->continued = 0;
			p = p->next;
		}
	}
}

static int	update_process_info(t_job *j, t_process *p, int status)
{
	p->status = status;
	if (WIFSTOPPED(status))
	{
		ft_dprintf(g_term_fd, "\n");
		p->stopped = 1;
		if (job_is_stopped(j))
			reset_job_status(j, 'c');
		job_notify();
	}
	if (WIFCONTINUED(status))
	{
		p->continued = 1;
		if (job_is_continued(j))
			reset_job_status(j, 's');
	}
	else if (WIFEXITED(status))
	{
		p->completed = 1;
		if (WIFSIGNALED (status))
			j->signal_num = WTERMSIG(status);
	}
	return (SUCCESS);
}

static int	check_process_changes(t_job *j, int cpid, int status)
{
	t_process	*p;

	int i = 0;
	p = j->first_process;
	while (p != NULL)
	{
		i++;
		if (p->pid == cpid)
			return (update_process_info(j, p, status));
		p = p->next;
	}
	return (-1);
}

/*
** When waitpid returns a pid, we check to which job that pid belongs to
** Then we update that process and the job strucutre.
*/

int			job_check_changes(pid_t cpid, int status)
{
	t_job		*j;

	j = g_job_ctrl->first_job;
	if (cpid > 0)
	{
		while (j != NULL)
		{
			if (check_process_changes(j, cpid, status) == 0)
				return (0);
			j = j->next;
		}
	}
	else if (cpid == 0)
		return (-1);
	return (-1);
}
