/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 13:01:20 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_reset_signals_pre_exec(void)
{
	signal(SIGWINCH, SIG_DFL);
}

static void	sh_reset_signals_post_exec(void)
{
	signal(SIGWINCH, handle_resize);
}

int			sh_pre_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_reset_shell(0) < 0)
			return (FAILURE);
		sh_reset_signals_pre_exec();
		ft_dprintf(g_term_fd, CYAN"PRE-EXECUTION\n"EOC);
	}
	else
		ft_dprintf(g_term_fd, CYAN"Non-interactive shell\n"EOC);

	return (SUCCESS);
}

int			sh_post_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_set_shell_back(0) < 0)
			return (FAILURE);
		sh_reset_signals_post_exec();
		ft_dprintf(g_term_fd, CYAN"POST-EXECUTION\n"EOC);
	}
	else
		ft_dprintf(g_term_fd, CYAN"Non-interactive shell\n"EOC);
	return (SUCCESS);
}
