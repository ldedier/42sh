/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 15:20:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sys/signal.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void			reset_signals(void)
{
	int i;

	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
	if (g_job_ctrl->cmd_subst)
		signal(SIGTSTP, SIG_IGN);
}

void			handler_sighup(int signo)
{
	if (signo == SIGHUP)
	{
		jobs_terminate();
		sh_post_execution();
		exit(128 + SIGHUP);
	}
}

void			handler_sigwinch(int signo)
{
	if (signo == SIGWINCH)
	{
		if (ioctl(g_term_fd, TIOCGWINSZ, &g_glob.winsize) == -1)
			exit(sh_reset_shell(1));
		if (isatty(g_term_fd) && g_glob.command_line.dy_str)
			render_command_line(&g_glob.command_line, 0, 1);
	}
}

void			init_signals(void)
{
	int i;

	i = 1;
	while (i <= 31)
	{
		if (i != SIGSTOP && i != SIGKILL)
			signal(i, SIG_IGN);
		i++;
	}
	signal(SIGCHLD, SIG_DFL);
	signal(SIGWINCH, handler_sigwinch);
}
