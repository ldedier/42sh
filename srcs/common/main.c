/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/31 08:21:19 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int	main_exit_value(t_shell *shell, int ret)
{
	int ret_save;

	ret_save = ret;
	if (shell->ret_value_set || shell->ret_value)
	{
		if (sh_verbose_exec())
			ft_dprintf(2, "Using ret_value\n", ret);
		ret = shell->ret_value;
	}
	if (sh_verbose_exec())
		ft_dprintf(2, "Final returned value : %d\n", ret);
	// mdaoud: 0 or g_term_fd?
	if (isatty(0) && ret_save != 2)
		ft_dprintf(2, "exit\n");
	if (g_term_fd != -1)
		close (g_term_fd);
	return (ret);
}

int			main(int argc, char **argv, char **env)
{
	t_shell		shell;
	int			ret;

	(void)argc;
	(void)argv;
	init_signals();
	if (jobs_init())
		return (FAILURE);
	if ((g_term_fd = open("/dev/tty", O_RDWR)) < 0)
		return (sh_perror(SH_ERR1_TTY, "main"));
	if (g_term_fd != TTY_FD)
	{
		if (sh_check_open_fd(0, TTY_FD) >= 0 || dup2(g_term_fd, TTY_FD) < 0)
			return (sh_perror(SH_ERR1_TTY, "Can't open fd 10"));
		close(g_term_fd);
		g_term_fd = TTY_FD;
	}
	if (!isatty(STDIN_FILENO))
		ret = sh_process_canonical_mode(&shell, env);
	else
	{
		if (sh_init_terminal(&shell, env) != SUCCESS)
			return (FAILURE);
		if (sh_init_shell(&shell, env) != SUCCESS)
		{
			sh_free_all(&shell);
			return (sh_reset_shell(FAILURE));
		}
		ret = sh_process_noncanonical_mode(&shell);
	}
	return (main_exit_value(&shell, ret));
}
