/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_stopped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:18:27 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/16 23:51:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** A job is considered stopped if all the process are stopped.
*/

int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed == 0 && p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
