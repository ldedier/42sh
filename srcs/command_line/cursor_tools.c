/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:33:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 23:03:57 by ldedier          ###   ########.fr       */
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

void	replace_cursor_on_index(void)
{
	char	*str;
	int		x;
	int		y;

	y = ((get_true_cursor_pos(g_glob.cursor)) / g_glob.winsize.ws_col)
		- g_glob.command_line.scrolled_lines;
	x = (get_true_cursor_pos(g_glob.cursor)) % g_glob.winsize.ws_col;
	str = tgetstr("do", NULL);
	while (y-- > 0)
		tputs(str, 1, putchar_int);
	str = tgetstr("nd", NULL);
	while (x-- > 0)
		tputs(str, 1, putchar_int);
}

void	replace_cursor_after_render(void)
{
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.command_line.nb_chars);
	replace_cursor_on_index();
}
