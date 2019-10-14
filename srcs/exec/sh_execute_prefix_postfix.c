/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/13 23:52:12 by mdaoud           ###   ########.fr       */
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

int		sh_pre_execution()
{
	if (g_job_ctrl->interactive)
	{
		if (sh_reset_shell(0) == ATTR_ERROR)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_pre_execution"));
		// sh_process_execute_close_pipes(context);
	}
	// ft_dprintf(g_term_fd, "PRE EXECUTION\n");
	sh_reset_signals_pre_exec();
	return (SUCCESS);
}

int		sh_post_execution(void)
{
	if (g_job_ctrl->interactive)
	{
		if (sh_set_shell_back(0) == ATTR_ERROR)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_post_execution"));
	}
	// ft_dprintf(g_term_fd, "POST EXECUTION\n");
	sh_reset_signals_post_exec();
	return (SUCCESS);
}

int		sh_pre_execution_pipes(t_list *contexts)
{
	(void)contexts;
	// shell is interactive?
	if (isatty(0) && sh_reset_shell(0) == ATTR_ERROR)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_pre_execution_pipes"));
		// sh_execute_pipe_sequence_close_pipes_list(contexts); //need to close pipe here in case of trouble!
	}
	sh_reset_signals_pre_exec();
	return (SUCCESS);
}