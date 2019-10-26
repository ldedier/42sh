/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/25 12:43:47 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"

static void		mark_job_as_running (t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p != NULL)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

static t_job	*get_active_job(void)
{
	t_job	*j;

	if (g_job_ctrl->first_job == NULL)
	{
		sh_perror("fg: current", "no such job");
		return (NULL);
	}
	j = g_job_ctrl->first_job;
	while (j->next != NULL && j->next->next != NULL)
		j = j->next;
	return (j);
}

int			sh_builtin_fg(t_context *context)
{
	t_job	*active_job;
	int		res;

	res = 0;
	active_job = get_active_job();
	if (active_job == NULL)
		return (ERROR);
	mark_job_as_running(active_job);
	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);	//put back
	ft_dprintf(g_term_fd, "[%d]  %s\n",
		active_job->number, active_job->command);
	if (job_put_in_fg(active_job, 1, &res) != SUCCESS)
		return (FAILURE);
	sh_env_update_ret_value_wait_result(context, res);
	return (SUCCESS);
}
