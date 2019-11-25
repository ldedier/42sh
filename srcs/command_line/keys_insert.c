/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:17:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 01:59:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_enter(t_command_line *command_line)
{
	if (command_line->autocompletion.head == NULL)
		return (process_enter_no_autocompletion(command_line));
	else
	{
		command_line->autocompletion.head = NULL;
		command_line->autocompletion.active = 0;
		render_command_line(command_line, 0, 1);
	}
	return (1);
}

int		sh_can_add_searcher(t_command_line *command_line)
{
	int research_nb_lines;
	int command_lines;

	command_lines = ft_max(1,
		(((get_true_cursor_pos(ft_strlen_utf8(command_line->dy_str->str))))
			/ g_glob.winsize.ws_col) + 1);
	research_nb_lines = get_research_nb_lines_n(command_line,
		ft_strlen_utf8(command_line->searcher.dy_str->str) + 1);
	if (command_lines - command_line->scrolled_lines > g_glob.winsize.ws_row)
		return (research_nb_lines < 2);
	else
		return (research_nb_lines +
			command_lines - command_line->scrolled_lines
				<= g_glob.winsize.ws_row
					+ command_line->scrolled_lines ? 1 : 0);
}

int		process_key_insert_printable_utf8(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
	unsigned char c;

	if (command_line->searcher.active)
	{
		if (sh_can_add_searcher(command_line))
		{
			if (sh_add_to_dy_str(command_line->searcher.dy_str, buffer->buff,
						buffer->progress))
				return (FAILURE);
			c = 0;
			if (sh_add_to_dy_str(command_line->searcher.dy_str, &c, 1))
				return (FAILURE);
			update_research_history(command_line, shell, 0);
		}
		else
			ring_bell();
	}
	else
	{
		if (sh_add_to_command(command_line, buffer->buff, buffer->progress))
			return (FAILURE);
		render_command_line(command_line, 1, 1);
	}
	flush_keys(buffer);
	return (SUCCESS);
}

int		insert_keys(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->progress == 1
		&& is_printable_utf8(buffer->buff, buffer->progress))
	{
		if (process_key_insert_printable_utf8(buffer,
				shell, command_line) != SUCCESS)
			return (FAILURE);
	}
	else if (buffer->buff[0] == 27
		&& (buffer->buff[1] == 91 || buffer->buff[1] == 79)
			&& buffer->buff[2] == 65)
		process_up(shell, command_line);
	else if (buffer->buff[0] == 27
		&& (buffer->buff[1] == 91 || buffer->buff[1] == 79)
			&& buffer->buff[2] == 66)
		process_down(shell, command_line);
	else if (buffer->buff[0] == 18)
	{
		if (process_research_history(command_line, shell))
			return (FAILURE);
	}
	else
		return (KEEP_READ);
	return (SUCCESS);
}

int		process_keys_insert(t_key_buffer *buffer,
		t_shell *shell, t_command_line *command_line)
{
	int ret;

	cancel_autocompletion(buffer, command_line);
	if (command_line->edit_style == E_EDIT_STYLE_READLINE &&
		(ret = process_keys_readline(buffer, shell, command_line)) != KEEP_READ)
		return (ret);
	if ((ret = insert_keys(buffer, shell, command_line) == KEEP_READ))
		return (process_keys_ret(buffer, shell, command_line));
	else if (ret)
		return (ret);
	flush_keys(buffer);
	return (KEEP_READ);
}
