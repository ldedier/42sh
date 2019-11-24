/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:30:51 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:18:21 by jmartel          ###   ########.fr       */
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
	{
		return (sh_perror("Could not add the process to a process group",
			"setpgid"));
	}
	return (SUCCESS);
}
