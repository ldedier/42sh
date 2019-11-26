/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_terminate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:10:52 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:16:34 by jmartel          ###   ########.fr       */
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
				kill(-j->pgid, SIGHUP);
				kill(-j->pgid, SIGCONT);
			}
			j = j->next;
		}
	}
}
