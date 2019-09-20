/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_job_by_pgid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:52:14 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 15:51:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"

t_job		*find_job_by_pgid(pid_t pgid)
{
	t_job *curr_job;

	curr_job = g_job_ctrl->first_job;
	while (curr_job != NULL)
	{
		if (curr_job->pgid == pgid)
			return curr_job;
		curr_job = curr_job->next;
	}
	return NULL;
}