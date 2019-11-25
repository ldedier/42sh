/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:15:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 14:03:14 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			job_control_free(void)
{
	t_job		*j;
	t_job		*j_next;

	// if (g_job_ctrl->interactive == 0)
	// {
	// 	free(g_job_ctrl);
	// 	return ;
	// }
	if (g_job_ctrl == NULL)
		return ;
	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		j_next = j->next;
		job_free(j);
		j = j_next;
	}
	free(g_job_ctrl);
	g_job_ctrl = NULL;
}
