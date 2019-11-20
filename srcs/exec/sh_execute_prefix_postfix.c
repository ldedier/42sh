/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 06:18:28 by mdaoud           ###   ########.fr       */
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
		// ft_dprintf(g_term_fd, COL_MAGENTA"Pre execution\n"EOC);
	}
	// else
		// ft_dprintf(g_term_fd, COL_MAGENTA"Non-interactive shell\n"EOC);
	return (SUCCESS);
}

int			sh_post_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_set_shell_back(0) < 0)
			return (FAILURE);
		sh_reset_signals_post_exec();
		// ft_dprintf(g_term_fd, COL_MAGENTA"Post execution\n"EOC);
	}
	// else
		// ft_dprintf(g_term_fd, COL_MAGENTA"Non-interactive shell\n"EOC);
	return (SUCCESS);
}
