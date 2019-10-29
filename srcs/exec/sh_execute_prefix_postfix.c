/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/29 15:06:41 by mdaoud           ###   ########.fr       */
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

int		sh_pre_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_reset_shell(0) < 0)
			return (FAILURE);
		// ft_dprintf(g_term_fd, "%sPRE EXECUTION%s\n", COL_MAGENTA, EOC);
		sh_reset_signals_pre_exec();
	}
	else
	{
		// ft_dprintf(g_term_fd, "%sNON-INTERACTIVE SHELL%s\n", COL_MAGENTA, EOC);
	}

	return (SUCCESS);
}

int		sh_post_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_set_shell_back(0) < 0)
			return (FAILURE);
		// ft_dprintf(g_term_fd, "%sPOST EXECUTION%s\n", COL_MAGENTA, EOC);
		sh_reset_signals_post_exec();
	}
	else
	{
		// ft_dprintf(g_term_fd, "%sNON-INTERACTIVE SHELL%s\n", COL_MAGENTA, EOC);
	}

	return (SUCCESS);
}