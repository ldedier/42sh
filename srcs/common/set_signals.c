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
		sh_reset_shell(0);
		exit(128 + SIGHUP);
	}
}

static void		handler_term_sig(int signo)
{
	jobs_terminate();
	sh_reset_shell(0);
	exit(128 + signo);
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
			signal(i, handler_term_sig);
		i++;
	}
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGWINCH, handler_sigwinch);
	signal(SIGHUP, handler_sighup);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
