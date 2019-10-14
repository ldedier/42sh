/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_continued.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:48:31 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/15 00:49:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** A job is considered completed if all the process are completed or stopped.
*/

int		job_is_continued(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->continued == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
