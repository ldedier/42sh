/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_put_in_fg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 23:22:03 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/30 01:34:14 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

static int	check_process_changes(t_job *j, int cpid, int status)
{
	t_process	*p;

	int i = 0;
	p = j->first_process;
	while (p != NULL)
	{
		i++;
		if (p->pid == cpid)
		{
			ft_dprintf(g_job_ctrl->term_fd, "CHECK PROCESS CHANGES: %d\n", cpid);
			p->status = status;
			if (WIFSTOPPED (status))
			{
				// ft_printf("\n"); //dprintf
				ft_dprintf(g_job_ctrl->term_fd, "process %d had been stopped\n"); //dprintf
				p->stopped = 1;
				job_notify();
			}
			else if (WIFCONTINUED(status))
				p->stopped = 0;
			else
			{
				p->completed = 1;
				if (WIFSIGNALED (status))
					j->signal_num = WTERMSIG(status);
			}
			return (0);
		}
		p = p->next;
	}
	// ft_dprintf(g_job_ctrl->term_fd, "job [%d] has %d processes\n", j->number, i);
}

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
		// tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
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
	// Put the shell back into the forground.
	if (tcsetpgrp(g_job_ctrl->term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		*res = FAILURE;
		return (jc_error_free("tcsetpgrp",
			"Could not give the shell control of the terminal", 1, FAILURE));
	}
	return (SUCCESS);

}