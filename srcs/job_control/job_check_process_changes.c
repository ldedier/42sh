/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_updates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:46:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 01:11:51 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int			job_check_process_changes(pid_t cpid, int status)
{
	t_job		*j;
	t_process	*p;

	j = g_job_ctrl->first_job;
	if (cpid > 0)
	{
		while (j != NULL)
		{
			p = j->first_process;
			while (p != NULL)
			{
				if (p->pid == cpid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
							ft_dprintf (STDERR_FILENO, "%d: Terminated by signal %d.\n",
								(int) cpid, WTERMSIG (p->status));
					}
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
	}
	else if (cpid == 0)
	{
		return (-1);
	}
	ft_dprintf(STDERR_FILENO, "waitpid\n");
	return (-1);
}