/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/19 18:27:18 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"
#include "sh_builtin.h"

static void		mark_job_as_running(t_job *j)
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

static int		sh_execute_bg(t_job *j, t_context *context)
{
	if (!job_is_stopped(j))
	{
		return (sh_perror_err("bg", "job already running in background"));
	}
	mark_job_as_running(j);
	ft_dprintf(g_term_fd, "[%d]  %s &\n",
		j->number, j->command);
	if (kill(-j->pgid, SIGCONT) < 0)
		return (sh_perror_err("bg", "Could not send SIGCONT to the process"));
	sh_env_update_ret_value_wait_result(context, SUCCESS);
	return (SUCCESS);
}

int				sh_builtin_bg(t_context *context)
{
	t_job	*j;
	int		i;
	int		job_lst[MAX_JOBS];

	if (!g_job_ctrl->interactive)
		return (sh_perror_err("bg", "no job control in this shell"));
	i = -1;
	while (++i < MAX_JOBS)
		job_lst[i] = -2;
	if ((parse_bg_args((char **)context->params->tbl, job_lst)) != SUCCESS)
		return (ERROR);
	if (job_lst[0] == -2)
		job_lst[0] = 0;
	i = -1;
	while (job_lst[++i] != -2)
	{
		if ((j = bg_get_job_by_spec(job_lst[i])) == NULL)
			return (ERROR);
		context->shell->ret_value_set = 0;
		if (sh_execute_bg(j, context) != SUCCESS)
			return (ERROR);
		if (context->shell->ret_value == 130)
			return (SUCCESS);
	}
	return (SUCCESS);
}
