/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:04:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/19 18:31:16 by mdaoud           ###   ########.fr       */
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

static int		sh_execute_fg(t_job *j, t_context *context)
{
	int		res;
	int		retvalue;

	res = SUCCESS;
	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	mark_job_as_running(j);
	ft_dprintf(g_term_fd, "[%d]  %s\n",
		j->number, j->command);
	if ((retvalue = job_put_in_fg(j, 1, &res)) != SUCCESS)
		return (retvalue);
	sh_env_update_ret_value_wait_result(context, res);
	return (SUCCESS);
}

int				sh_builtin_fg(t_context *context)
{
	t_job	*j;
	int		i;
	int		job_lst[MAX_JOBS];
	int		ret;

	if (!g_job_ctrl->interactive)
		return (sh_perror_err("fg", "no job control in this shell"));
	i = -1;
	while (++i < MAX_JOBS)
		job_lst[i] = -2;
	if ((parse_fg_args((char **)context->params->tbl, job_lst)) != SUCCESS)
		return (ERROR);
	job_lst[0] = (job_lst[0] == -2 ? 0 : job_lst[0]);
	i = -1;
	while (job_lst[++i] != -2)
	{
		if ((j = fg_get_job_by_spec(job_lst[i])) == NULL)
			return (ERROR);
		context->shell->ret_value_set = 0;
		if ((ret = sh_execute_fg(j, context)) != SUCCESS)
			return (ret);
		if (context->shell->ret_value == 130)
			return (SUCCESS);
	}
	return (SUCCESS);
}
