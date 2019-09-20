/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:22:03 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 00:03:51 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

int			job_put_in_fg(t_job *j, int cont)
{
	if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->curr_job->pgid) < 0)
			return (ERROR);
	if (cont) ;
		// Send cont signal
	job_wait(g_job_ctrl->curr_job);
	// if (WIFSIGNALED(res))
	// 	ft_printf("Was terminated by a signal\n");
	if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->shell_pgid) < 0)
			return (ERROR);

}