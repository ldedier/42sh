/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 05:57:09 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:13:38 by jmartel          ###   ########.fr       */
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
	while (j != NULL && j->number != num)
		j = j->next;
	return (j);
}

t_job			*job_get_by_sign(char c)
{
	t_job	*j;

	if (!g_job_ctrl->interactive)
		return (NULL);
	j = g_job_ctrl->first_job;
	while (j != NULL && j->sign != c)
		j = j->next;
	return (j);
}
