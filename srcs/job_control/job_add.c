/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:09:20 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/14 23:45:57 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "sh_21.h"

int			job_add(void)
{
	t_job	*j;
	t_job	*it;

	ft_printf("%sADDING JOB: %d%s\n", COLOR_RED, g_job_control->job_count, COLOR_END);
	if ((j = malloc(sizeof(t_job))) == NULL)
		return (FAILURE);
	j->number = g_job_control->job_count;
	j->first_process = NULL;
	j->next = NULL;
	j->notified = 0;
	j->empty_process = 1;
	j->pgid = 0;
	j->command = NULL;	//	Fill it with the command
	g_job_control->job_count = g_job_control->job_count + 1;
	if (g_job_control->first_job == NULL)
	{
		g_job_control->first_job = j;
		return (SUCCESS);
	}
	it = g_job_control->first_job;
	while (it->next != NULL)
		it = it->next;
	it->next = j;
	return (SUCCESS);
}