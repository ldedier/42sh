/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:24:10 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/18 09:53:42 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"


static void		init_jc_values(void)
{
	int i = 0;

	while (i < MAX_JOBS)
		g_job_ctrl->job_num[i++] = 0;
	g_job_ctrl->first_job = NULL;
	g_job_ctrl->job_cmd = NULL;
	g_job_ctrl->curr_job = NULL;
	g_job_ctrl->job_added = 0;
	g_job_ctrl->ampersand_eol = 0;
	g_job_ctrl->ampersand = 0;
	// This is where we print all job-control realted messages
	// g_term_fd = open("/dev/tty", O_RDWR); //Protect
}

static int		jc_set_process_group(void)
{
	g_job_ctrl->shell_pgid = getpid();
	// Put the shell in its own process group
	if (setpgid (g_job_ctrl->shell_pgid, g_job_ctrl->shell_pgid) < 0)
	{
		free(g_job_ctrl);
		return (sh_perror("setpgid",
			"Could not put the shell in its own process group"));
	}
	// Take control of the terminal
	if (tcsetpgrp(g_term_fd, g_job_ctrl->shell_pgid) < 0)
	{
		free(g_job_ctrl);
		return (sh_perror("tcsetpgrp",
			"Could not take control of the terminal"));
	}
	return (EXIT_SUCCESS);
}

/*
** Initialize job control
** interactive means that the shell is running inside the terminal
** A shell that is not running interactlvely should not handle job control.
** If the shell is run from the background, kill it immediatly.
*/

int				jobs_init(void)
{
	g_job_ctrl = malloc(sizeof(t_job_control));
	if (g_job_ctrl == NULL)
		return (sh_perror(SH_ERR1_MALLOC, "jobs_init"));
	init_jc_values();
	// Check whether the shell in run interactively
	// g_job_ctrl->interactive = 0;
	g_job_ctrl->interactive = isatty(STDIN_FILENO);

	if (g_job_ctrl->interactive)
	{
		// If the shell in run as a background process, quit.
		if(tcgetpgrp (g_term_fd) != (g_job_ctrl->shell_pgid = getpgrp ()))
			if (kill (- g_job_ctrl->shell_pgid, SIGHUP) < 0)
			{
				free(g_job_ctrl);
				return (sh_perror("kill", "Could not properly close the shell"));
			}
		signal(SIGTTOU, SIG_IGN);	//	signal handling needs rework
		if (jc_set_process_group() < 0)
			return (FAILURE);
		return (SUCCESS);
	}
	// free(g_job_ctrl);
	return (SUCCESS);
}