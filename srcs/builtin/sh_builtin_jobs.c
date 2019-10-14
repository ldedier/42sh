/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/15 01:57:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"

static void		print_job_status(t_job *j)
{
	if (job_is_completed(j))
		ft_printf("[%d]\tCompleted\t\t%s\n", j->number, j->command);
	else if (job_is_stopped(j))
		ft_printf("[%d]\tStopped\t\t%s\n", j->number, j->command);
	else
		ft_printf("[%d]\tRunning\t\t%s\n", j->number, j->command);
}

int				sh_builtin_jobs(t_context *context)
{
	t_job	*j;

	(void)context;
	if (g_job_ctrl->first_job == NULL)
		return (SUCCESS);
	j = g_job_ctrl->first_job;
	while (j != NULL && !job_is_completed(j))
	{
		print_job_status(j);
		j = j->next;
	}
	return (0);
}
