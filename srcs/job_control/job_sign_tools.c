/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_sign_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 06:00:38 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 11:04:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			job_reset_sign(char c)
{
	t_job	*j;

	if (c == '+')
		j = job_get_by_sign('+');
	else if (c == '-')
		j = job_get_by_sign('-');
	else
		return ;
	if (j != NULL)
		j->sign = ' ';
}

void			job_set_plus_sign(t_job *j)
{
	t_job	*curr;

	if (!g_job_ctrl->interactive)
		return ;
	job_reset_sign('-');
	curr = job_get_by_sign('+');
	if (curr != NULL)
		curr->sign = '-';
	if (j != NULL)
		j->sign = '+';
}

t_job			*job_get_unsigned(void)
{
	t_job	*res;
	t_job	*j;

	if (!g_job_ctrl->interactive)
		return (NULL);
	res = NULL;
	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		if (j->sign != '-' && j->sign != '+')
			res = j;
		j = j->next;
	}
	return (res);
}

void			job_added_update_sign(t_job *j)
{
	t_job	*tmp;

	tmp = job_get_by_sign('+');
	if (tmp == NULL || !job_is_stopped(tmp))
		job_set_plus_sign(j);
	else
	{
		tmp = job_get_by_sign('-');
		if (tmp == NULL || !job_is_stopped(tmp))
		{
			job_reset_sign('-');
			j->sign = '-';
		}
	}
}

void			job_exited_update_sign(char j_sign)
{
	t_job	*tmp;

	if (j_sign == ' ')
		return ;
	else if (j_sign == '+')
	{
		tmp = job_get_by_sign('-');
		if (tmp != NULL)
			tmp->sign = '+';
		else
			tmp = job_get_unsigned();
		if (tmp != NULL)
			tmp->sign = '+';
	}
	tmp = job_get_unsigned();
	if (tmp != NULL)
		tmp->sign = '-';
}
