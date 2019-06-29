/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:27:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/15 17:31:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_c(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.head = NULL;
	command_line->autocompletion.active = 0;
	if (command_line->searcher.active == 0)
	{
		get_down_from_command(command_line);
		reset_command_line(shell, command_line);
	}
	command_line->searcher.active = 0;
	render_command_line(command_line, 0, 1);
	return (CTRL_C);
}

int		process_ctrl_d(t_shell *shell, t_command_line *command_line)
{
	if (command_line->dy_str->current_size == 0
			&& (command_line->context == E_CONTEXT_STANDARD
				|| command_line->context == E_CONTEXT_HEREDOC))
	{
		if (command_line->context == E_CONTEXT_STANDARD)
		{
			shell->running = 0;
			ft_dprintf(0, "exit\n");
		}
		return (CTRL_D);
	}
	else
		ring_bell();
	return (KEEP_READ);
}