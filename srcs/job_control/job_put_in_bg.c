/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/01 00:03:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

pid_t		get_last_process_pid(t_job *j)
{
	t_process	*p;

	if (j == NULL)
		return (0);
	p = j->first_process;
	if (p == NULL)
		return (0);
	while (p != NULL && p->next != NULL)
		p = p->next;
	return (p->pid);
}

int			job_put_in_bg(t_job *j, int cont)
{
	pid_t	pid;

	pid = get_last_process_pid(j);
	j->foreground = 0;
	if (cont)
		if (kill (- j->pgid, SIGCONT) < 0)
		{
			ft_dprintf(STDERR_FILENO, "kill");
			return (ERROR);
		}
	ft_dprintf(g_job_ctrl->term_fd, "[%d] %d\n", j->number, pid);
	return (SUCCESS);
}