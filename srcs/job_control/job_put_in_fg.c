/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:22:03 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/14 12:25:17 by mdaoud           ###   ########.fr       */
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
		return (sh_perror_err("fg", "Could not send SIGCONT to the process"));
	if (tcsetpgrp(g_term_fd, j->pgid) < 0)
		return (sh_perror("tcsetpgrp",
			"Could not put the job in the foreground"));
	// ft_dprintf(g_term_fd, "%sJob [%d] in control\n%s", COLOR_YELLOW, j->number, EOC);
	j->foreground = 1;
	job_wait(j, ret);
	job_notify();
	g_glob.command_line.interrupted = WIFSIGNALED(*ret) || WIFSTOPPED(*ret);
	if (sh_post_execution() != SUCCESS)
		return (FAILURE);
	ft_dprintf(g_term_fd, YELLOW"Postfix in put_in_fg\n"EOC);	
	// ft_dprintf(g_term_fd, "%sjob [%d] returned%s\n", COLOR_YELLOW, j->number, COLOR_END);
	if (tcsetpgrp(g_term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		return (sh_perror("tcsetpgrp",
			"Could not give the shell control of the terminal"));
	}
	// ft_dprintf(g_term_fd, "%sShell control\n%s", COLOR_YELLOW, EOC);
	return (SUCCESS);
}