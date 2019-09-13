/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_stopped_completed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:54:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/11 17:56:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int			job_stopped_completed(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed == 0 && p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}