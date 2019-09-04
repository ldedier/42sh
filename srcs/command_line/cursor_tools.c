/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:33:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/03 17:15:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_true_cursor_pos_prev_prompt(int cursor)
{
	int ret;

	if (g_glob.command_line.scrolled_lines)
		return (cursor + ft_strlen_utf8(ELIPTIC_COMMAND_LINE));
	if (g_glob.command_line.prev_prompt_len != -1)
	{
		ret = cursor + g_glob.command_line.prev_prompt_len;
		g_glob.command_line.prev_prompt_len = -1;
	}
	else
		ret = (cursor + ft_strlen_utf8(g_glob.command_line.prompt));
	return (ret);
}

int		get_true_cursor_pos(int cursor)
{
	if (!g_glob.command_line.scrolled_lines)
		return (cursor + ft_strlen_utf8(g_glob.command_line.prompt));
	else
		return (cursor + ft_strlen_utf8(ELIPTIC_COMMAND_LINE));
}

int		get_down_from_command(t_command_line *command_line)
{
	int		full_y;
	int		cursor_y;
	int		i;
	char	*str;
	int		ret;

	ret = 0;
	full_y = (get_true_cursor_pos(command_line->nb_chars)
		/ g_glob.winsize.ws_col) - command_line->scrolled_lines;
	cursor_y = (get_true_cursor_pos(g_glob.cursor)
		/ g_glob.winsize.ws_col) - command_line->scrolled_lines;
	str = tgetstr("do", NULL);
	i = cursor_y;
	while (i < full_y && i < g_glob.winsize.ws_row - 1)
	{
		tputs(str, 1, putchar_int);
		i++;
		ret++;
	}
	tputs(str, 1, putchar_int);
	i = 0;
	while (i++ < cursor_y)
		ret++;
	return (ret + 1);
}

void	replace_cursor_on_index(void)
{
	char	*str;
	int		x;
	int		y;

	y = ((get_true_cursor_pos(g_glob.cursor)) / g_glob.winsize.ws_col)
		- g_glob.command_line.scrolled_lines;
	x = (get_true_cursor_pos(g_glob.cursor)) % g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	while (y--)
		tputs(str, 1, putchar_int);
	str = tgetstr("nd", NULL);
	while (x--)
		tputs(str, 1, putchar_int);
}

void	replace_cursor_after_render(void)
{
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.command_line.nb_chars);
	replace_cursor_on_index();
}
