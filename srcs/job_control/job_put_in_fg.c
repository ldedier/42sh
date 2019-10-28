/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:22:03 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/27 11:15:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** To put a job in the foreground:
** We first need to give it control of the terminal (syscall <tcsetpgrp>).
** If we want to continue the previously stopped job, we set <cont> to 1.
** Then the shell needs to wait for the job to report back.
** After the job is done (waitpid returns):
**	1) If the job was stopped or killed by a signal, we need to make sure-
**		that the terminal attributes are reset back as we want them.
**	2) We need to give the shell back control of the terminal.
*/

int			job_put_in_fg(t_job *j, int cont, int *ret)
{
	if (cont && kill (- j->pgid, SIGCONT) < 0)
	{
		return (jobs_error_free("kill",
			"Could not send SIGCONT to the process", 0, FAILURE));
	}
	if (tcsetpgrp(g_term_fd, j->pgid) < 0)
	{
		return (jobs_error_free("tcsetpgrp",
			"Could not put the job in the foreground", 0, FAILURE));
	}
	// ft_dprintf(g_term_fd, "%sJob [%d] in control\n%s", COLOR_YELLOW, j->number, EOC);
	j->foreground = 1;
	// Wait for the job
	job_wait(j, ret);
	job_notify();
	g_glob.command_line.interrupted = WIFSIGNALED(*ret) || WIFSTOPPED(*ret);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
	// ft_dprintf(g_term_fd, "%sjob [%d] returned%s\n", COLOR_YELLOW, j->number, COLOR_END);
	// Put the shell back into the forground.
	if (tcsetpgrp(g_term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		return (jobs_error_free("tcsetpgrp",
			"Could not give the shell control of the terminal", 1, FAILURE));
	}
	// ft_dprintf(g_term_fd, "%sShell control\n%s", COLOR_YELLOW, EOC);
	return (SUCCESS);
}