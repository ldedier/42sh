/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:39:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/07 15:02:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			switch_command_line(t_command_line *command_line,
				char *str, int start)
{
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (sh_perror(SH_ERR1_MALLOC, "restore_command_line"));
	update_command_line(command_line, start);
	replace_cursor_vim_legal(command_line);
	return (SUCCESS);
}

int			switch_command_line_index(t_command_line *command_line,
				char *str, int index)
{
	flush_command_line(command_line);
	if (ft_dy_str_cpy_str(command_line->dy_str, str))
		return (sh_perror(SH_ERR1_MALLOC, "restore_command_line"));
	update_command_line_index(command_line, index);
	replace_cursor_vim_legal(command_line);
	return (SUCCESS);
}

int			process_history_down(t_shell *shell, t_command_line *command_line,
				int count, int start)
{
	int		i;
	t_entry *entry;

	if (!shell->history.head->prev)
	{
		ring_bell();
		return (SUCCESS);
	}
	i = 0;
	while (i < count && shell->history.head != shell->history.commands)
	{
		shell->history.head = shell->history.head->prev;
		i++;
	}
	if (i < count)
	{
		if (i < count - 1)
			ring_bell();
		shell->history.head = &shell->history.head_start;
		return (switch_command_line(command_line, command_line->edit_line, 0));
	}
	entry = (t_entry *)shell->history.head->content;
	sh_init_entry_saves(entry);
	return (switch_command_line(command_line, entry->command, start));
}

int			reached_history_end(t_shell *shell)
{
	return (shell->history.head->next == shell->history.commands
		&& shell->history.head != &shell->history.head_start);
}

int			process_history_up(t_shell *shell, t_command_line *command_line,
				int count, int start)
{
	int			i;
	t_entry		*entry;

	if (!shell->history.commands)
	{
		ring_bell();
		return (SUCCESS);
	}
	if (shell->history.head == &shell->history.head_start)
	{
		ft_strdel(&command_line->edit_line);
		if (!(command_line->edit_line = ft_strdup(command_line->dy_str->str)))
			return (FAILURE);
	}
	i = 0;
	while (i < count && !reached_history_end(shell))
	{
		shell->history.head = shell->history.head->next;
		i++;
	}
	if (i < count)
		ring_bell();
	entry = (t_entry *)shell->history.head->content;
	sh_init_entry_saves(entry);
	return (switch_command_line(command_line, entry->command, start));
}
