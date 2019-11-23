/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 13:24:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 11:03:21 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		job_remove(t_job *j)
{
	t_job	*tmp;
	t_job	*prev;

	if (j == NULL)
		return ;
	tmp = g_job_ctrl->first_job;
	prev = tmp;
	if (tmp == j)
	{
		g_job_ctrl->first_job = j->next;
		job_free(j);
		return ;
	}
	while (tmp != NULL && tmp != j)
	{
		prev = tmp;
		tmp = tmp->next;
	}
}
