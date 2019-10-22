/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 05:57:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/22 09:24:26 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_job			*job_get_by_num(int num)
{
	t_job	*j;

	if (num >= MAX_JOBS || num < 0 || !g_job_ctrl->interactive)
		return (NULL);
	j = g_job_ctrl->first_job;
	if (j == NULL)
		return (NULL);
	while (j->next != NULL && j->number != num)
		j = j->next;
	if (j->next == NULL)
		return (NULL);
	return (j);
}

t_job		*job_get_by_sign(char c)
{
	t_job	*j;

	if (!g_job_ctrl->interactive)
		return (NULL);
	j = g_job_ctrl->first_job;
	while (j != NULL && j->sign != c)
		j = j->next;
	return (j);
}


