/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:38:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/10 01:26:10 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	transmit_sig_and_exit(int signal)
{
	if (g_parent)
	{
		kill(g_parent, signal);
		waitpid(g_parent, NULL, 0);
	}
	ft_dprintf(0, "exit\n");
	exit(sh_reset_shell(0));
}

void	handle_stp(int sgnl)
{
	(void)sgnl;
	// sh_reset_shell(0);
	// signal(SIGTSTP, SIG_DFL);
	// if (ioctl(0, TIOCSTI, "\x1a") == -1)
	// 	exit(sh_reset_shell(1));
	ft_dprintf(g_term_fd, "%sReceived SIGTSTP from pid: %d%s\n", RED, getpid(), EOC);
}

void	handle_cont(int sgnl)
{
	signal(SIGTSTP, handle_stp);
	sh_set_shell_back(0);
	handle_resize(sgnl);
}
