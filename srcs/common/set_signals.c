/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:05:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 13:12:28 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sys/signal.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// int		process_ctrl_c(t_shell *shell, t_command_line *command_line)
// {
// 	process_cancel_autocompletion(command_line);
// 	if (command_line->searcher.active == 0)
// 	{
// 		get_down_from_command(command_line);
// 		reset_command_line(shell, command_line);
// 	}
// 	command_line->searcher.active = 0;
// 	if (sh_env_update_ret_value_and_question(shell, SH_RET_CTRL_C))
// 		return (FAILURE);
// 	render_command_line(command_line, 0, 1);
// 	return (CTRL_C);
// }

void			reset_signals(void)
{
	int i;

	// ft_dprintf(g_term_fd, "Resetting Signals\n");
	i = 1;
	while (i <= 31)
		signal(i++, SIG_DFL);
	// if (g_job_ctrl->cmd_subst)
	// 	signal(SIGTSTP, SIG_IGN);
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

void		handler_sigwinch(int signo)
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
		signal(i++, SIG_DFL);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handle_int);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, handler_sigwinch);
	signal(SIGHUP, handler_sighup);
}
