/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_jobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/22 02:07:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"

static void		print_job_status(t_job *j)
{
	if (job_is_completed(j))
		ft_printf("completed");
	else if (job_is_stopped(j))
		ft_printf("stopped");
	else
		ft_printf("running");
	ft_printf("  ");
}

int				sh_builtin_jobs(t_context *context)
{
	t_job	*j;
	t_process	*p;

	ft_printf("Shell pgid: %d\n", g_job_ctrl->shell_pgid);
	if (g_job_ctrl->first_job == NULL)
		return (SUCCESS);
	j = g_job_ctrl->first_job;
	while (j != NULL && !job_is_completed(j))
	{
		ft_printf("[%d]\t", j->number);
		print_job_status(j);
		p = j->first_process;
		while (p != NULL)
		{
			ft_printf("%d\t", p->pid);
			str_tab_print(p->argv);
			ft_printf("\n\t\t ");
			p = p->next;
		}
		j = j->next;
	}
	return (0);
}
