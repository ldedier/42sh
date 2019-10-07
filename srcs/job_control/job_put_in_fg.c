/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:22:03 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/06 18:12:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int			job_put_in_fg(t_job *j, int cont, int *res)
{
	if (tcsetpgrp(g_job_ctrl->term_fd, j->pgid) < 0)
	{
		*res = ERROR;
		return (jc_error_free("tcsetpgrp",
			"Could not put the job in the foreground", 0, ERROR));
	}
	if (cont)
	{
		if (kill (- j->pgid, SIGCONT) < 0)
		{
			*res = ERROR;
			return (jc_error_free("kill",
				"Could not send SIGCONT to the process", 0, ERROR));
		}
	}
	j->foreground = 1;
	// Wait for the job
	job_wait(g_job_ctrl->curr_job, res);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
	// ft_dprintf(g_job_ctrl->term_fd, "%sDone waiting%s\n", COLOR_YELLOW, COLOR_END);
	// Put the shell back into the forground.
	if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		*res = FAILURE;
		return (jc_error_free("tcsetpgrp",
			"Could not give the shell control of the terminal", 1, FAILURE));
	}
	return (SUCCESS);

}