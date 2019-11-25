/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:43:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 10:06:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_escape_sequence(t_shell *shell,
			t_command_line *command_line, t_key_buffer *buffer)
{
	command_line->searcher.active = 0;
	if ((buffer->buff[1] == 91 || buffer->buff[1] == 79)
		&& buffer->buff[2] == 67)
		process_right(shell, command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79)
		&& buffer->buff[2] == 68)
		process_left(shell, command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79)
		&& buffer->buff[2] == 51 && buffer->buff[3] == 126)
		process_suppr(command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79)
		&& buffer->buff[2] == 72)
		process_start(command_line);
	else if ((buffer->buff[1] == 91 || buffer->buff[1] == 79)
		&& buffer->buff[2] == 70)
		process_end(command_line);
	else if ((buffer->buff[1] == 91 && buffer->buff[2] == 49 &&
		buffer->buff[3] == 59 && buffer->buff[4] == 50))
		return (process_shift(buffer, command_line));
	else
		return (SUCCESS);
	flush_keys(buffer);
	return (SUCCESS);
}

int		process_shift(t_key_buffer *buffer, t_command_line *command_line)
{
	if (buffer->buff[5] == 67
			&& command_line->current_index
				< (int)command_line->dy_str->current_size)
		process_shift_right(command_line);
	else if (buffer->buff[5] == 68)
		process_shift_left(command_line);
	else if (buffer->buff[5] == 65)
		process_shift_up(command_line);
	else if (buffer->buff[5] == 66)
		process_shift_down(command_line);
	else
		return (SUCCESS);
	flush_keys(buffer);
	return (SUCCESS);
}

int		process_keys(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->buff[0] == 27)
	{
		if (buffer->progress == 1 && !await_stream(0))
		{
			if (command_line->edit_style == E_EDIT_STYLE_VIM)
				return (process_escape(shell, command_line, buffer));
		}
		else
			return (process_escape_sequence(shell, command_line, buffer));
	}
	else if (buffer->buff[0] == 12)
		process_clear(command_line);
	else if (buffer->buff[0] == 127 && command_line->mode != E_MODE_COMMAND)
		process_delete(command_line, shell);
	else
		return (SUCCESS);
	flush_keys(buffer);
	return (SUCCESS);
}

int		process_get_keys(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
	int res;

	process_keys(buffer, shell, command_line);
	if (buffer->progress)
	{
		if (command_line->mode == E_MODE_INSERT)
		{
			res = process_keys_insert(buffer, shell, command_line);
			if (res == FAILURE || (command_line->context != E_CONTEXT_HEREDOC
						&& res != KEEP_READ && res != CTRL_C)
					|| (command_line->context != E_CONTEXT_STANDARD
						&& res != KEEP_READ))
				return (res);
		}
		else if ((res = process_keys_others(buffer,
			shell, command_line)) != KEEP_READ)
		{
			if (res == RETURN_COMMAND)
				return (SUCCESS);
			else
				return (KEEP_READ);
		}
	}
	return (KEEP_READ);
}

int		get_keys(t_shell *shell, t_command_line *cl)
{
	int			res;

	ft_bzero(cl->buffer.buff, READ_BUFF_SIZE);
	cl->buffer.progress = 0;
	cl->buffer.last_char_input = -1;
	cl->buffer.persistent = 1;
	while (1)
	{
		if (!shell->running)
			return (SUCCESS);
		if (read(g_term_fd, &cl->buffer.buff[cl->buffer.progress++], 1) < 0)
			return (sh_perror(SH_ERR1_READ, "get_keys"));
		if ((res = process_get_keys(&cl->buffer, shell, cl)) != KEEP_READ)
			return (res);
		if (cl->buffer.progress >= READ_BUFF_SIZE
			|| (cl->buffer.progress &&
				should_flush_buffer(cl->buffer, cl)))
		{
			flush_keys(&cl->buffer);
		}
	}
}
