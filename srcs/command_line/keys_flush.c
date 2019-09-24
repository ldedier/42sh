/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_flush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:20:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/05 15:20:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	flush_keys(t_key_buffer *buffer)
{
	if (buffer->progress)
	{
		buffer->last_char_input = buffer->buff[0];
		ft_bzero(buffer->buff, READ_BUFF_SIZE);
		buffer->progress = 0;
	}
}

int		flush_keys_ret(t_key_buffer *buffer, int ret)
{
	flush_keys(buffer);
	return (ret);
}

int		should_flush_buffer(t_key_buffer buffer, t_command_line *command_line)
{
	if (buffer.progress > 1 && buffer.buff[0] == 27
		&& buffer.buff[1] != 91 && buffer.buff[1] != 79)
		return (1);
	if (command_line->mode == E_MODE_INSERT
		|| command_line->mode == E_MODE_REPLACE)
	{
		if (buffer.buff[0] < 32 && buffer.buff[0] != 27)
			return (1);
	}
	else
	{
		if (buffer.buff[0] != 27)
			return (1);
	}
	return (0);
}
