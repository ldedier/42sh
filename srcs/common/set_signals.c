/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/29 23:31:28 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sys/signal.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void		handler_sigchld(int signo)
{
	if (signo == SIGCHLD && g_job_ctrl)
	{
		// if (g_job_ctrl->jc_enabled && g_job_ctrl->curr_job->pipe_node != PIPE_JOB)
		if (g_job_ctrl->jc_enabled)
			job_notify();
	}
}
void			reset_signals(void)
{
	int i;

	i = 1;
	while (i <= SIGUSR2)
		signal(i++, SIG_DFL);
	signal(SIGCHLD, handler_sigchld);
}

void	sigtstp_handler(int signal)
{
	if (g_parent)
	{
		kill(g_parent, signal);
		kill(g_parent, SIGTTIN);
		kill(g_parent, SIGTTOU);
	}
	if (isatty(0) && g_glob.command_line.dy_str)
	{
		get_down_from_command(&g_glob.command_line);
		g_glob.cursor = 0;
		g_glob.command_line.dy_str->current_size = 0;
		g_glob.command_line.current_index = 0;
		ft_bzero(g_glob.command_line.dy_str->str,
				g_glob.command_line.dy_str->max_size);
		g_glob.command_line.nb_chars = 0;
		render_command_line(&g_glob.command_line, 0, 1);
	}
}


// static void		handler_sigusr1(int signo, siginfo_t *info, void *context)
// {
// 	if (signo == SIGUSR1)
// 	{
// 		ft_printf("RECEIVED SIGUSR1 from %d\n", info->si_pid);
// 		if (g_job_ctrl->jc_enabled)
// 		{
// 			ft_printf("Adding it to job number [%d]\n", g_job_ctrl->curr_job->number);
// 			process_add(NULL, info->si_pid);
// 		}
// 	}
// }

// static void		set_sigusr1_action(void)
// {
// 	struct sigaction	s_act;

// 	ft_memset(&s_act, '\0', sizeof(s_act));
// 	s_act.sa_sigaction = handler_sigusr1;
// 	s_act.sa_flags = SA_SIGINFO;
// 	sigaction(SIGUSR1, &s_act, NULL);
// }

static void		init_signal2(void (*default_func)(int))
{

	// set_sigusr1_action();
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCHLD, handler_sigchld);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGUSR1, default_func);
	signal(SIGUSR2, default_func);
	signal(SIGQUIT, transmit_sig_no_motion);
	signal(SIGINT, handler_sigint);
	signal(SIGHUP, default_func);
	signal(SIGABRT, default_func);
	signal(SIGTERM, transmit_sig_and_exit);
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
