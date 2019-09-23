/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:39:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/04/20 16:51:41 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	ring_bell(void)
{
	char *str;

	str = tgetstr("bl", NULL);
	tputs(str, 1, putchar_int);
}

void	process_edit_command_left(t_command_line *command_line)
{
	if (command_line->current_index > 0)
	{
		command_line->current_index = get_left_w_char_index(command_line);
		render_command_line(command_line, -1, 1);
	}
	else
		ring_bell();
}

void	process_edit_command_right(t_command_line *command_line)
{
	int limit;

	if (command_line->mode != E_MODE_COMMAND)
		limit = command_line->dy_str->current_size;
	else
		limit = command_line->dy_str->current_size - 1;
	if (command_line->current_index < limit)
	{
		command_line->current_index = get_right_w_char_index(command_line);
		render_command_line(command_line, 1, 1);
	}
	else
		ring_bell();
}
