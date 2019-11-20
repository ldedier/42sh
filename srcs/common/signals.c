/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 08:53:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 16:30:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** mdaoud:
** Since the change in signal handling, this file is no longer needed.
** But I kept it just in case
*/

pid_t		g_parent = 0;

void		transmit_sig_no_motion(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
}

void		transmit_sig_and_die(int signal)
{
	if (g_parent)
		kill(g_parent, signal);
	exit(sh_reset_shell(0));
}

void		default_sig_bonus(int sgnl)
{
	if (g_parent)
	{
		kill(g_parent, sgnl);
		waitpid(g_parent, NULL, 0);
	}
	signal(sgnl, SIG_DFL);
	sh_reset_shell(0);
	kill(getpid(), sgnl);
}

void		default_sig(int sgnl)
{
	if (g_parent)
	{
		kill(g_parent, sgnl);
		waitpid(g_parent, NULL, 0);
	}
	sh_reset_shell(0);
	exit(0);
}

void		handle_resize(int signal)
{
	(void)signal;
	if (ioctl(0, TIOCGWINSZ, &g_glob.winsize) == -1)
		exit(sh_reset_shell(1));
	if (isatty(0) && g_glob.command_line.dy_str)
		render_command_line(&g_glob.command_line, 0, 1);
}
