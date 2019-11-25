/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_ret.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:15:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 07:20:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_process_keys_ret(t_key_buffer *buffer,
			t_shell *shell, t_command_line *command_line)
{
	int ret;

	if (buffer->buff[0] == 10)
	{
		if (process_enter(command_line) == 0)
			return (SUCCESS);
	}
	else if (buffer->buff[0] == 4)
	{
		if (process_ctrl_d(shell, command_line) != KEEP_READ)
			return (CTRL_D);
	}
	else if (buffer->buff[0] == 9)
	{
		if (process_tab(shell, command_line) == FAILURE)
			return (FAILURE);
		flush_keys(buffer);
	}
	else if (buffer->buff[0] == 3)
	{
		ret = (process_ctrl_c(shell, command_line));
		return (flush_keys_ret(buffer, ret));
	}
	return (KEEP_READ);
}

int		process_keys_ret(t_key_buffer *buffer, t_shell *shell,
			t_command_line *command_line)
{
	int ret;

	if ((ret = process_process_keys_ret(buffer, shell, command_line))
		!= KEEP_READ)
		return (ret);
	else
		return (KEEP_READ);
}
