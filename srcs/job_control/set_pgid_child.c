/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pgid_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:29:26 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/01 17:06:31 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int					set_pgid_child(int cpid)
{
	int	ret;

	cpid = getpid();
	if ((ret = set_child_pgid(cpid)) != SUCCESS)
		return (ret);
	if (g_job_ctrl->curr_job->foreground == 1 && !g_job_ctrl->pipe_node)
		if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->curr_job->pgid) < 0)
			return (jc_error_free("tcsetpgrp",
				"Could not give terminal control to the process", 1, FAILURE));
	return (SUCCESS);
}