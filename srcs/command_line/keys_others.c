/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:21:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:20:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	process_keys_command(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	int ret;

	(void)shell;
	command_line->current_count = &command_line->count;
	if (ft_isdigit(command_line->buffer.buff[0])
		&& (command_line->count.active
		|| command_line->buffer.buff[0] != '0'))
	{
		if (add_digit_and_update(command_line, command_line->buffer.buff[0]))
			return (FAILURE);
		flush_keys(buffer);
		return (SUCCESS);
	}
	command_line->count.value = command_line->count.tmp_value;
	command_line->count.tmp_value = 1;
	ret = execute_vim_command(command_line, buffer->buff[0]);
	command_line->count.active = 0;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (ret);
}

static int	process_keys_visual(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	if (buffer->buff[0] == 'y')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		command_line->mode = E_MODE_COMMAND;
		update_prompt(shell, command_line);
		render_command_line(command_line, 0, 1);
		flush_keys(buffer);
	}
	else if (buffer->buff[0] == 'd')
	{
		if (copy_selection_to_clipboard(command_line) != SUCCESS)
			return (FAILURE);
		command_line->mode = E_MODE_COMMAND;
		update_prompt(shell, command_line);
		delete_command_line_selection(command_line);
		render_command_line(command_line, 0, 1);
		flush_keys(buffer);
	}
	return (SUCCESS);
}

int			replace_command_line(t_key_buffer *buffer,
				t_command_line *command_line)
{
	int len;

	if (is_printable_utf8(buffer->buff, buffer->progress))
	{
		if (command_line->current_index ==
			(int)command_line->dy_str->current_size)
		{
			if (sh_add_to_command(command_line, buffer->buff, buffer->progress))
				return (FAILURE);
			render_command_line(command_line, 1, 1);
		}
		else
		{
			len = get_char_len_unprotected(command_line->current_index,
				(unsigned char *)command_line->dy_str->str);
			buffer->buff[buffer->progress] = 0;
			if (ft_substitute_dy_str(command_line->dy_str, (char *)buffer->buff,
				command_line->current_index, len))
				return (FAILURE);
			render_command_line(command_line, 1, 1);
			command_line->current_index += len;
		}
		flush_keys(buffer);
	}
	return (SUCCESS);
}

int			process_keys_others(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
	if (command_line->mode == E_MODE_COMMAND)
		return (process_keys_command(buffer, shell, command_line));
	else if (command_line->mode == E_MODE_VISUAL)
		return (process_keys_visual(buffer, shell, command_line));
	else if (command_line->mode == E_MODE_REPLACE)
		return (replace_command_line(buffer, command_line));
	else
		return (SUCCESS);
}
