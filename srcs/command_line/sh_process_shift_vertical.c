/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_shift_vertical.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:47:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/19 11:41:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_shift_up(t_command_line *command_line)
{
	int		cursor;
	t_xy	xy;
	t_xy	xy_iter;

	cursor = g_glob.cursor;
	xy = get_position(get_true_cursor_pos(g_glob.cursor));
	while (command_line->current_index > 0)
	{
		command_line->current_index = get_left_w_char_index(command_line);
		xy_iter = get_position(get_true_cursor_pos(--cursor));
		if (xy_iter.x == xy.x && xy_iter.y == xy.y - 1)
		{
			render_command_line(command_line, cursor - g_glob.cursor, 1);
			return (SUCCESS);
		}
	}
	render_command_line(command_line, cursor - g_glob.cursor, 1);
	return (SUCCESS);
}

int		process_shift_down(t_command_line *command_line)
{
	int		cursor;
	t_xy	xy;
	t_xy	xy_iter;

	cursor = g_glob.cursor;
	xy = get_position(get_true_cursor_pos(g_glob.cursor));
	while (command_line->current_index
		< (int)command_line->dy_str->current_size)
	{
		command_line->current_index = get_right_w_char_index(command_line);
		xy_iter = get_position(get_true_cursor_pos(++cursor));
		if (xy_iter.x == xy.x && xy_iter.y == xy.y + 1)
		{
			render_command_line(command_line, cursor - g_glob.cursor, 1);
			replace_cursor_vim_legal(command_line);
			return (SUCCESS);
		}
	}
	render_command_line(command_line, cursor - g_glob.cursor, 1);
	replace_cursor_vim_legal(command_line);
	return (SUCCESS);
}
