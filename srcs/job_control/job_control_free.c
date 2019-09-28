/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:15:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/28 23:55:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			job_control_free(void)
{
	t_job		*j;
	t_job		*j_next;

	if (g_job_ctrl->shell_interactive == 0)
	{
		free(g_job_ctrl);
		return ;
	}
	if (g_job_ctrl == NULL)
		return ;
	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		// ft_printf("Freeing job [%d]\n\t", j->number);
		j_next = j->next;
		job_free(j);
		j = j_next;
	}
	free(g_job_ctrl);
	g_job_ctrl = NULL;
}