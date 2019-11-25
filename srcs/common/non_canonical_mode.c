/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 16:29:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int		sh_await_command(t_shell *shell)
{
	int ret;

	if ((ret = sh_get_command(shell, &g_glob.command_line)) != SUCCESS)
	{
		if (g_job_ctrl->interactive)
			job_notify();
		return (ret);
	}
	shell->exec_depth = 0;
	if ((ret = execute_command(shell, g_glob.command_line.dy_str->str, 1)))
		return (ret);
	if (g_job_ctrl->interactive)
		job_notify();
	return (ret);
}

int				sh_process_noncanonical_mode(t_shell *shell)
{
	while (shell->running)
	{
		if (sh_await_command(shell) == FAILURE)
		{
			sh_free_all(shell);
			return (sh_reset_shell(FAILURE));
		}
	}
	jobs_terminate();
	sh_free_all(shell);
	return (sh_reset_shell(SUCCESS));
}
