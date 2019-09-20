/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_child_pgid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:02:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 23:06:49 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int			set_child_pgid(pid_t cpid)
{
	if (g_job_ctrl->curr_job->pgid == 0)
		g_job_ctrl->curr_job->pgid = cpid;
	if (setpgid(cpid, g_job_ctrl->curr_job->pgid) < 0)
		return (ERROR);
	return (SUCCESS);
}