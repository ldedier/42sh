/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 10:38:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/09 02:31:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

// void	handler_sigint(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_dprintf(g_job_ctrl->term_fd, "SIGINT FROM %d\n", getpid());
// 		if (isatty(0) && g_glob.command_line.dy_str)
// 		{
// 			get_down_from_command(&g_glob.command_line);
// 			reset_command_line(g_glob.command_line.shell, &g_glob.command_line);
// 			sh_env_update_ret_value_and_question(g_glob.command_line.shell,
// 				SH_RET_CTRL_C);
// 			render_command_line(&g_glob.command_line, 0, 1);
// 			sh_set_term_sig(0);
// 			ioctl(0, TIOCSTI, "\x03");
// 		}
// 	}
// }

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
	sh_reset_shell(0);
	signal(SIGTSTP, SIG_DFL);
	if (ioctl(0, TIOCSTI, "\x1a") == -1)
		exit(sh_reset_shell(1));
}

void	handle_cont(int sgnl)
{
	signal(SIGTSTP, handle_stp);
	sh_set_shell_back(0);
	handle_resize(sgnl);
}
