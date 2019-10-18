/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:29:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/09 01:42:40 by mdaoud           ###   ########.fr       */
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

int					set_pgid_child(int cpid)
{
	cpid = getpid();
	if (g_job_ctrl->curr_job->pgid == 0)
		g_job_ctrl->curr_job->pgid = cpid;
	// setpgid adds process with pid <cpid> in the process group with gpid <pgid>
	if (setpgid(cpid, g_job_ctrl->curr_job->pgid) < 0)
		return (jobs_error_free("setpgid",
			"Could not add the process to a process group", 0, ERROR));
	// If in foreground, give the job control of terminal (syscall tcsetpgrp).
	if (g_job_ctrl->curr_job->foreground == 1)
		if (tcsetpgrp(g_term_fd, g_job_ctrl->curr_job->pgid) < 0)
			return (jobs_error_free("tcsetpgrp",
				"Could not give terminal control to the process", 1, FAILURE));
	return (SUCCESS);
}