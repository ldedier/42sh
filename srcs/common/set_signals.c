/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/31 17:44:55 by mdaoud           ###   ########.fr       */
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
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
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

static void		handler_terminating_sig(int signo)
{
	if (signo == SIGALRM || signo == SIGEMT || signo == SIGIO ||
		signo == SIGPIPE || signo == SIGPROF || signo == SIGUSR1 ||
		signo == SIGUSR2 || signo == SIGVTALRM || signo == SIGALRM ||
		signo == SIGBUS || signo == SIGFPE || signo == SIGILL ||
		signo == SIGIOT || signo == SIGSEGV || signo == SIGSYS ||
		signo == SIGTRAP || signo == SIGXCPU || signo == SIGXFSZ)
		{
			jobs_terminate();
			sh_post_execution();
			exit(128 + signo);
		}
}

static void		set_term_sig_handler(void)
{
	signal(SIGALRM, handler_terminating_sig);
	signal(SIGEMT, handler_terminating_sig);
	signal(SIGIO, handler_terminating_sig);
	signal(SIGPIPE, handler_terminating_sig);
	signal(SIGPROF, handler_terminating_sig);
	signal(SIGUSR1, handler_terminating_sig);
	signal(SIGUSR2, handler_terminating_sig);
	signal(SIGVTALRM, handler_terminating_sig);
}

static void		set_core_sig_handler(void)
{
	signal(SIGABRT, handler_terminating_sig);
	signal(SIGBUS, handler_terminating_sig);
	signal(SIGFPE, handler_terminating_sig);
	signal(SIGILL, handler_terminating_sig);
	signal(SIGIOT, handler_terminating_sig);
	signal(SIGSEGV, handler_terminating_sig);
	signal(SIGSYS, handler_terminating_sig);
	signal(SIGTRAP, handler_terminating_sig);
	signal(SIGXCPU, handler_terminating_sig);
	signal(SIGXFSZ, handler_terminating_sig);
}

void			init_signals(void)
{
	int i;

	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGHUP, handler_sighup);
	set_term_sig_handler();
	set_core_sig_handler();
}
