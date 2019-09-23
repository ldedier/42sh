/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_prefix_postfix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:20:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/31 13:49:37 by ldedier          ###   ########.fr       */
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
	if (isatty(0) && sh_reset_shell(0) == ATTR_ERROR)
	{
		// sh_process_execute_close_pipes(context);
		return (FAILURE);
	}
	sh_reset_signals_pre_exec();
	return (SUCCESS);
}

int		sh_pre_execution_pipes(t_list *contexts)
{
	(void)contexts;
	if (isatty(0) && sh_reset_shell(0) == ATTR_ERROR)
	{
		// sh_execute_pipe_sequence_close_pipes_list(contexts); //need to close pipe here in case of troubles!
		return (FAILURE);
	}
	sh_reset_signals_pre_exec();
	return (SUCCESS);
}

int		sh_post_execution(void)
{
	if (isatty(0) && sh_set_shell_back(0) == ATTR_ERROR)
	{
		return (sh_perror("Could not modify this terminal attributes",
			"sh_init_terminal"));
	}
	sh_reset_signals_post_exec();
	return (SUCCESS);
}
