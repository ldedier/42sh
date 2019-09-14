/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:59:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/14 23:46:47 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

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
	if (isatty(0) && ret_save != 2)
		ft_dprintf(2, "exit\n");
	return (ret);
}

static int	sh_init_job_control_attr(t_shell *shell)
{
	// g_job_control = malloc(sizeof(t_job_control));
	// if (g_job_control == NULL)
	// 	return (FAILURE);
	// g_job_control->job_count = 1;
	// g_job_control->first_job = NULL;
	// if (setpgid (g_job_control->shell_pgid, g_job_control->shell_pgid) < 0)
	// {
	// 	ft_dprintf(STDERR_FILENO, "setpgid\n");	//sh_perror
	// 	exit (FAILURE);
	// }
	return (init_job_control(shell));
	// return (SUCCESS);
}

int			main(int argc, char **argv, char **env)
{
	t_shell		shell;
	int			ret;

	(void)argc;
	(void)argv;
	init_signals();
	if (!isatty(0))
		ret = sh_process_canonical_mode(&shell, env);
	else
	{
		if (sh_init_terminal(&shell, env) != SUCCESS)
			return (FAILURE);
		if (sh_init_shell(&shell, env) != SUCCESS ||
			sh_init_job_control_attr(&shell) != SUCCESS)
		{
			sh_free_all(&shell);
			return (sh_reset_shell(FAILURE));
		}
		ret = sh_process_noncanonical_mode(&shell);
	}
	return (main_exit_value(&shell, ret));
}
