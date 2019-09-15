/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:39:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 15:39:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	update_command_line(t_command_line *command_line)
{
	command_line->current_index = command_line->dy_str->current_size;
	command_line->nb_chars = ft_strlen_utf8(command_line->dy_str->str);
}

int			process_history_down(t_shell *shell, t_command_line *command_line)
{
	char *str;

	if (!shell->history.head->prev)
		return (SUCCESS);
	if (shell->history.head == shell->history.commands)
	{
		shell->history.head = &shell->history.head_start;
		if (ft_strcmp(command_line->dy_str->str, ""))
		{
			flush_command_line(command_line);
			update_command_line(command_line);
			render_command_line(command_line,
				command_line->nb_chars - g_glob.cursor, 1);
		}
		return (SUCCESS);
	}
	shell->history.head = shell->history.head->prev;
	str = ((t_entry *)shell->history.head->content)->command;
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (FAILURE);
	update_command_line(command_line);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}

int			process_history_up(t_shell *shell, t_command_line *command_line)
{
	char *str;

	if (!shell->history.commands)
		return (SUCCESS);
	if (shell->history.head->next == shell->history.commands
		&& shell->history.head != &shell->history.head_start)
		return (SUCCESS);
	shell->history.head = shell->history.head->next;
	str = ((t_entry *)shell->history.head->content)->command;
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (FAILURE);
	update_command_line(command_line);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}
