/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_active_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:05:11 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/26 03:04:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"


t_job		*get_active_job(void)
{
	t_job	*j;
	t_job	*prev;

	j = g_job_ctrl->first_job;
	if (j == NULL)
		return (NULL);
	while (j->next != NULL && j->next->pgid != 0)
	{
		prev = j;
		j = j->next;
	}
	return (j);
}