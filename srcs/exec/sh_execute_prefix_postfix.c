/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/21 14:37:16 by jdugoudr         ###   ########.fr       */
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
		if (sh_reset_shell(0) == ATTR_ERROR)
			return (sh_perror("Could not modify this terminal attributes",
				"sh_pre_execution"));
		// sh_process_execute_close_pipes(context);
	}
	ft_dprintf(2, "bonjour on est la pre\n");
	// ft_dprintf(g_term_fd, "%sPRE EXECUTION%s\n", COL_MAGENTA, EOC);
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
	// ft_dprintf(g_term_fd, "%sPOST EXECUTION%s\n", COL_MAGENTA, EOC);
	ft_dprintf(2, "bonjour on est la post\n");
	sh_reset_signals_post_exec();
	return (SUCCESS);
}

// int		sh_pre_execution_pipes(t_list *contexts)
// {
// 	(void)contexts;
// 	// shell is interactive?
// 	if (isatty(0) && sh_reset_shell(0) == ATTR_ERROR)
// 	{
// 		return (sh_perror("Could not modify this terminal attributes",
// 			"sh_pre_execution_pipes"));
// 		// sh_execute_pipe_sequence_close_pipes_list(contexts); //need to close pipe here in case of trouble!
// 	}
// 	sh_reset_signals_pre_exec();
// 	return (SUCCESS);
// }
