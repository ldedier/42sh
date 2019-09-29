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

static int	check_process_changes(t_job *j, int cpid, int status)
{
	t_process	*p;

	int i = 0;
	p = j->first_process;
	while (p != NULL)
	{
		i++;
		if (p->pid == cpid)
		{
			p->status = status;
			if (WIFSTOPPED (status))
			{
				ft_printf("\n"); //dprintf
				p->stopped = 1;
				job_notify();
			}
			else if (WIFCONTINUED(status))
				p->stopped = 0;
			else
			{
				p->completed = 1;
				if (WIFSIGNALED (status))
					j->signal_num = WTERMSIG(status);
			}
			return (0);
		}
		p = p->next;
	}
}

int			job_check_changes(pid_t cpid, int status)
{
	t_job		*j;
	t_process	*p;

	j = g_job_ctrl->first_job;
	if (cpid > 0)
	{
		while (j != NULL)
		{
			check_process_changes(j, cpid, status);
			j = j->next;
		}
	}
	else if (cpid == 0)
		return (-1);
	return (-1);
}
