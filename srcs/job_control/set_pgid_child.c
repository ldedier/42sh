/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:29:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:17:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** The child of a fork needs to put itself in the proper process group.
** If the job->pgid is 0, it means that the job has no processes yet,
**	in which case the child will appoint itself as the group leader.
**	and make the job pgid equal to its pid (pid of the child).
** If the job->pgid is not 0, it means that there is already a leader.
**	in which case the child will take the pgid of the job.
**	(i.e: the pid of the group leader).
** After the child is added to the process group,
**	if the job was added in foreground, we give it control of the terminal.
*/

int			set_pgid_child(int cpid)
{
	cpid = getpid();
	if (g_job_ctrl->curr_job->pgid == 0)
		g_job_ctrl->curr_job->pgid = cpid;
	if (setpgid(cpid, g_job_ctrl->curr_job->pgid) < 0)
	{
		return (sh_perror("Could not add the process to a process group",
			"set_pgid_child"));
	}
	if (g_job_ctrl->curr_job->foreground == 1)
	{
		if (tcsetpgrp(g_term_fd, g_job_ctrl->curr_job->pgid) < 0)
			return (sh_perror("Could not give terminal control to the process",
				"set_pgid_child"));
	}
	return (SUCCESS);
}
