/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:45:01 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 20:53:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	keys_readline_ctrl_no_errors(t_key_buffer *buffer,
		t_command_line *command_line)
{
	if (buffer->buff[0] == 24 && buffer->last_char_input == 24)
		process_ctrl_x_x(command_line);
	else if (buffer->buff[0] == 2)
		process_edit_command_left(command_line);
	else if (buffer->buff[0] == 6)
		process_edit_command_right(command_line);
	else if (buffer->buff[0] == 1)
		process_start(command_line);
	else if (buffer->buff[0] == 5)
		process_end(command_line);
	else
		return (KEEP_READ);
	return (SUCCESS);
}

static int	keys_readline_ctrl(t_key_buffer *buffer, t_shell *shell,
		t_command_line *command_line)
{
	int ret;

	ret = SUCCESS;
	if (keys_readline_ctrl_no_errors(buffer, command_line) == SUCCESS)
		return (ret);
	else if (buffer->buff[0] == 11)
		ret = process_ctrl_k(command_line);
	else if (buffer->buff[0] == 20)
		ret = process_ctrl_t(command_line);
	else if (buffer->buff[0] == 21)
		ret = process_ctrl_u(command_line);
	else if (buffer->buff[0] == 23)
		ret = process_ctrl_w(command_line);
	else if (buffer->buff[0] == 25)
		ret = process_ctrl_y(command_line);
	else if (buffer->buff[0] == 14)
		ret = process_history_down(shell, command_line, 1, 0);
	else if (buffer->buff[0] == 16)
		ret = process_history_up(shell, command_line, 1, 0);
	else if (buffer->buff[0] == 31)
		ret = sh_restore_save(command_line);
	return (ret);
}

int			process_keys_readline(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	int ret;

	ret = SUCCESS;
	if (buffer->buff[0] == 27)
	{
		if (buffer->buff[1] == 102)
			ret = process_alt_f(command_line);
		else if (buffer->buff[1] == 98)
			ret = process_alt_b(command_line);
		else if (buffer->buff[1] == 100)
			ret = process_alt_d(command_line);
		else if (buffer->buff[1] == 116)
			ret = process_alt_t(command_line);
	}
	else
		ret = keys_readline_ctrl(buffer, shell, command_line);
	return (ret != SUCCESS ? ret : KEEP_READ);
}
