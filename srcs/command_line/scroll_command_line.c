/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 01:58:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_command_line_starting_index2(int scrolled_lines)
{
	int nb_lines;
	int	j;
	int res;
	int len;
	int	tmp;

	res = 0;
	nb_lines = 0;
	len = ft_strlen(g_glob.command_line.dy_str->str);
	while (nb_lines < scrolled_lines)
	{
		j = 0;
		while (j < g_glob.winsize.ws_col)
		{
			tmp = get_char_len2(res, len,
				(unsigned char *)g_glob.command_line.dy_str->str);
			if (tmp == -1)
				break ;
			res += tmp;
			j++;
		}
		nb_lines++;
	}
	return (res);
}

/*
** returns the index of the starting character of the command_line to print
*/

int		get_command_line_starting_index(t_command_line *command_line)
{
	int nb_lines;
	int	j;
	int res;
	int len;

	res = 0;
	nb_lines = 0;
	len = ft_strlen(g_glob.command_line.dy_str->str);
	while (nb_lines < command_line->scrolled_lines)
	{
		j = 0;
		while (j < g_glob.winsize.ws_col)
		{
			res += get_char_len2(res, len,
				(unsigned char *)g_glob.command_line.dy_str->str);
			j++;
		}
		nb_lines++;
	}
	return (res);
}

int		should_elipse_end(t_command_line *command_line, int scrolled_lines)
{
	int index;
	int add;

	index = get_command_line_starting_index2(scrolled_lines);
	add = get_command_line_prefix_len(command_line);
	if (add + ft_strlen_utf8(&command_line->dy_str->str[index])
		> (g_glob.winsize.ws_row) * g_glob.winsize.ws_col - 1)
		return (1);
	else
		return (0);
}

int		get_scroll_to_add(t_command_line *command_line,
			int target_screen_line, int research_nb_lines)
{
	if (target_screen_line < 1)
	{
		if (command_line->scrolled_lines + target_screen_line > 0)
			return (target_screen_line - 1);
		else
			return (target_screen_line);
	}
	else if (target_screen_line >= g_glob.winsize.ws_row
				- 1 - research_nb_lines)
	{
		if (should_elipse_end(command_line, command_line->scrolled_lines +
			target_screen_line - g_glob.winsize.ws_row + 1 + research_nb_lines))
			return (target_screen_line - g_glob.winsize.ws_row
				+ research_nb_lines + 2);
		else
			return (target_screen_line - g_glob.winsize.ws_row
				+ research_nb_lines + 1);
	}
	else
		return (0);
}

int		sh_scroll_command_line(t_command_line *command_line,
			int cursor, int cursor_inc)
{
	int true_cursor;
	int target_screen_line;
	int ret;
	int	research_nb_lines;

	research_nb_lines = get_research_nb_lines(command_line);
	true_cursor = get_true_cursor_pos_prev_prompt(cursor);
	while (!should_elipse_end(command_line, command_line->scrolled_lines)
		&& command_line->scrolled_lines
		&& g_glob.winsize.ws_row - research_nb_lines
			> command_line_nb_rows(command_line))
		command_line->scrolled_lines--;
	target_screen_line = ((true_cursor + cursor_inc) / g_glob.winsize.ws_col)
		- command_line->scrolled_lines;
	ret = get_scroll_to_add(command_line, target_screen_line,
		research_nb_lines);
	command_line->scrolled_lines += ret;
	return (ret);
}
