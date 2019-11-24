/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 17:27:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 20:55:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_c(t_shell *shell, t_command_line *command_line)
{
	process_cancel_autocompletion(command_line);
	if (command_line->searcher.active == 0)
	{
		get_down_from_command(command_line);
		reset_command_line(shell, command_line);
	}
	command_line->searcher.active = 0;
	if (sh_env_update_ret_value_and_question(shell, SH_RET_CTRL_C))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (CTRL_C);
}

int		process_ctrl_d(t_shell *shell, t_command_line *command_line)
{
	if (command_line->dy_str->current_size == 0)
	{
		if (command_line->context == E_CONTEXT_STANDARD
			|| command_line->context == E_CONTEXT_BACKSLASH)
			shell->running = 0;
		return (CTRL_D);
	}
	else if (command_line->edit_style == E_EDIT_STYLE_READLINE)
		process_suppr(command_line);
	return (KEEP_READ);
}
