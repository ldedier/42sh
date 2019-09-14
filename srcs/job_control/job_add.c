/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:09:20 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/14 18:45:00 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "sh_21.h"

int			job_add(void)
{
	t_job	*j;
	t_job	*it;

	if ((j = malloc(sizeof(t_job))) == NULL)
		return (FAILURE);
	j->number = g_job_count;
	j->first_process = NULL;
	j->next = NULL;
	j->notified = 0;
	j->empty_process = 1;
	j->pgid = 0;
	j->command = NULL;	//	Fill it with the command
	g_job_count = g_job_count + 1;
	if (g_first_job == NULL)
	{
		g_first_job = j;
		return (SUCCESS);
	}
	it = g_first_job;
	while (it->next != NULL)
		it = it->next;
	it->next = j;
	return (SUCCESS);
}