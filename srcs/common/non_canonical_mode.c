/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_canonical_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:41:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/18 14:56:24 by mdaoud           ###   ########.fr       */
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
		{
			jobs_free_cmds();
			job_notify();
		}
		return (ret);
	}
	shell->exec_depth = 0;
	ret = execute_command(shell, g_glob.command_line.dy_str->str, 1);
	if (g_job_ctrl->interactive)
	{
		jobs_free_cmds();
		job_notify();
	}
	return (ret);
}

int		sh_process_noncanonical_mode(t_shell *shell)
{
	while (shell->running)
	{
		if (sh_await_command(shell) == FAILURE)
		{
			sh_free_all(shell);
			return (sh_reset_shell(FAILURE));
		}
	}
	sh_free_all(shell);
	return (sh_reset_shell(SUCCESS));
}
