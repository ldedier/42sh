/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:59:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/21 17:58:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_down(t_shell *shell, t_command_line *command_line)
{
	if (command_line->autocompletion.head)
		return (process_autocompletion_down(shell, command_line));
	else
	{
		command_line->autocompletion.active = 0;
		return (process_historic_down(shell, command_line));
	}
}

int		process_up(t_shell *shell, t_command_line *command_line)
{
	if (command_line->autocompletion.head)
		return (process_autocompletion_up(command_line));
	else
	{
		command_line->autocompletion.active = 0;
		return (process_historic_up(shell, command_line));
	}
}

int		process_left(t_shell *shell, t_command_line *command_line)
{
	(void)shell;
	if (command_line->autocompletion.head)
		return (process_autocompletion_left(command_line));
	else
	{
		command_line->autocompletion.active = 0;
		process_edit_command_left(command_line);
	}
	return (SUCCESS);
}

int		process_right(t_shell *shell, t_command_line *command_line)
{
	(void)shell;
	if (command_line->autocompletion.head)
		return (process_autocompletion_right(command_line));
	else
	{
		command_line->autocompletion.active = 0;
		process_edit_command_right(command_line);
	}
	return (SUCCESS);
}
