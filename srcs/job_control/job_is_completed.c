/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:19:55 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/08 20:41:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

/*
** A job is considered completed if all the process are completed.
*/

int		job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
