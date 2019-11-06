/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_terminate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:10:52 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/30 21:47:12 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			jobs_terminate(void)
{
	t_job	*j;

	if (g_job_ctrl && g_job_ctrl->interactive)
	{
		j = g_job_ctrl->first_job;
		while (j != NULL)
		{
			if (j->pgid != 0)
			{
				kill (- j->pgid, SIGCONT);
				kill (- j->pgid, SIGHUP);
			}
			j = j->next;
		}
	}
}