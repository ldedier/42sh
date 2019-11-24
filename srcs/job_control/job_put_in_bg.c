/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:10:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:11:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** Putting the job in background only means printing the message on terminal.
** Since it's in the background we don't have to wait for it.
** cont: if the job was previously stopped and we want to continue it.
*/

int			job_put_in_bg(t_job *j)
{
	t_process	*p;

	if (j == NULL || j->first_process == NULL)
	{
		return (sh_perror("job_put_in_bg",
				"Cannot put the job in the background"));
	}
	j->foreground = 0;
	j->notified = 1;
	ft_dprintf(g_term_fd, "[%d]  ", j->number);
	p = j->first_process;
	while (p != NULL)
	{
		ft_dprintf(g_term_fd, "%d ", p->pid);
		p = p->next;
	}
	ft_dprintf(g_term_fd, "\n");
	return (SUCCESS);
}
