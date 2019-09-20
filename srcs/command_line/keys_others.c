/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:21:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/02 14:47:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
static int	process_p(t_command_line *command_line,
			t_key_buffer *buffer)
{
	if (paste_current_index(command_line, command_line->clipboard)
			!= SUCCESS)
		return (FAILURE);
	flush_keys(buffer);
	return (SUCCESS);
}
*/

static void	add_digit(t_command_count *count, char c)
{
	int n;

	n = c - '0';
	if (!count->active || count->tmp_value >= 10000)
		count->tmp_value = n;
	else
		count->tmp_value = count->tmp_value * 10 + c - '0';
	count->active = 1;
}

static int	process_keys_command(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	int ret;

	(void)shell;
	// old way olalala	
	/* 
	if (buffer->buff[0] == 'p')
		return (process_p(command_line, buffer));
	else if (buffer->buff[0] == 'i')
		return (process_i(shell, command_line, buffer));
	else if (buffer->buff[0] == 'v')
		return (process_v(shell, command_line, buffer));
	else if (buffer->buff[0] == 'd' && buffer->last_char_input == 'd'
		&& command_line->dy_str->current_size)
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
		flush_command_line(command_line);
		render_command_line(command_line, -g_glob.cursor, 1);
		flush_keys(buffer);
	}
	else if (buffer->buff[0] == 'y' && buffer->last_char_input == 'y')
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
		flush_keys(buffer);
	}
	*/

//	ft_printf("progress: %d\n", buffer->progress);
//	ft_printf("char: %d (%c)\n", buffer->buff[0], buffer->buff[0]);

	if (ft_isdigit(command_line->buffer.buff[0])
		&& (command_line->count.active
		|| command_line->buffer.buff[0] != '0'))
	{
		add_digit(&command_line->count, command_line->buffer.buff[0]);
		if (update_prompt(command_line->shell, command_line))
			return (FAILURE);
		render_command_line(command_line, 0, 1);
		//ft_printf("wip: %d\n", command_line->count.tmp_value);
		flush_keys(buffer);
		return (SUCCESS);
	}
	//ft_printf("sent: %d\n", command_line->count.tmp_value);
	command_line->count.value = command_line->count.tmp_value;
	command_line->count.tmp_value = 1;
	ret = execute_vim_command(command_line, buffer->buff[0]);
	command_line->count.active = 0;
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

int			process_keys_others(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
//	if (buffer->buff[0] == 3)
//		return (process_i(shell, command_line, buffer));
	if (command_line->mode == E_MODE_COMMAND)
		return (process_keys_command(buffer, shell, command_line));
	else if (command_line->mode == E_MODE_VISUAL)
		return (process_keys_visual(buffer, shell, command_line));
	else
		return (SUCCESS);
}
