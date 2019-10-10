/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:30:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/10 01:45:42 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int				set_pgid_parent(int cpid)
{
	int		ret;

	if ((ret = process_add(cpid)) != SUCCESS)
		return (ret);
	if (g_job_ctrl->curr_job->pgid == 0)
		g_job_ctrl->curr_job->pgid = cpid;
	if (setpgid(cpid, g_job_ctrl->curr_job->pgid) < 0)
		return (jobs_error_free("setpgid",
			"Could not add the process to a process group", 0, ERROR));
	// ft_dprintf(1, "Added process: %s", (char **)context->params->tbl[0]);
	// ft_dprintf(1, "\tpid: %d, pgid: %d to job [%d]\n", cpid, getpgid(cpid), g_job_ctrl->curr_job->number);
	return (SUCCESS);
}
