/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/01 00:21:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sys/signal.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// static void		handler_sigchld(int signo, siginfo_t *info, void *context)
// {
// 	if (signo == SIGCHLD)
// 	{
// 		ft_dprintf(g_job_ctrl->term_fd, "%sReceived SIGCHILD from <%d>%s\n",
// 				COLOR_PINK, info->si_pid, COLOR_END);
// 		job_notify();
// 	}
// }

// static void		set_sigchld_sigaction(void)
// {
// 	struct sigaction	s_act;

// 	ft_memset(&s_act, '\0', sizeof(s_act));
// 	s_act.sa_sigaction = handler_sigchld;
// 	s_act.sa_flags = SA_SIGINFO;
// 	sigaction(SIGCHLD, &s_act, NULL);
// }


static void		handler_sigchld(int signo)
{
	if (signo == SIGCHLD)
	{
		if (g_job_ctrl && g_job_ctrl->jc_enabled)
			if (g_job_ctrl->curr_job && !g_job_ctrl->curr_job->pipe_node)
				job_notify();
	}
}

static void		handler_sigtstp_pipe(int signo)
{
	if (signo == SIGTSTP)
	{
		signal(SIGTSTP, SIG_DFL);
		kill(getpid(), SIGTSTP);
		kill(getppid(), SIGCHLD);
		// signal(SIGTSTP, handler_sigtstp_pipe);
	}
}

void			reset_signals(void)
{
	int i;

	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
}

// void			set_signals_pipe(void)
// {
// 	int i;

// 	i = 1;
// 	while (i <= 31)
// 		signal(i++, SIG_DFL);
// 	signal(SIGTSTP, handler_sigtstp_pipe);
// }

static void		init_signal2(void (*default_func)(int))
{

	signal(SIGCHLD, handler_sigchld);
	signal(SIGQUIT, transmit_sig_no_motion);
	signal(SIGTERM, transmit_sig_and_exit);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGUSR1, default_func);
	signal(SIGUSR2, default_func);
	signal(SIGHUP, default_func);
	signal(SIGABRT, default_func);
	// set_sigchld_sigaction();
}

void			init_signals(void)
{
	void (*default_func)(int);

	if (BONUS_REDIRECT_SIGNAL)
		default_func = default_sig_bonus;
	else
		default_func = default_sig;
	signal(SIGIO, transmit_sig_no_motion);
	signal(SIGXCPU, default_func);
	signal(SIGXFSZ, default_func);
	signal(SIGVTALRM, default_func);
	signal(SIGPROF, default_func);
	signal(SIGINFO, transmit_sig_no_motion);
	signal(SIGURG, transmit_sig_no_motion);
	signal(SIGWINCH, handle_resize);
	signal(SIGILL, default_func);
	signal(SIGTRAP, default_func);
	signal(SIGEMT, default_func);
	signal(SIGFPE, default_func);
	signal(SIGBUS, default_func);
	signal(SIGSEGV, default_func);
	signal(SIGSYS, default_func);
	signal(SIGPIPE, transmit_sig_and_die);
	signal(SIGALRM, default_func);
	init_signal2(default_func);
}
