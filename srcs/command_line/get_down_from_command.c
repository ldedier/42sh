/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_down_from_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:37:24 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 20:38:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		process_get_down_from_command(int i, int full_y,
	int cursor_y, int research_nb_lines)
{
	char	*str;
	int		ret;

	ret = 0;
	str = tgetstr("do", NULL);
	while (i < full_y && i < g_glob.winsize.ws_row - 1 - research_nb_lines)
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

int				get_down_from_command(t_command_line *command_line)
{
	int		full_y;
	int		cursor_y;
	int		i;
	int		research_nb_lines;

	full_y = (get_true_cursor_pos(command_line->nb_chars)
		/ g_glob.winsize.ws_col) - command_line->scrolled_lines;
	cursor_y = (get_true_cursor_pos(g_glob.cursor)
		/ g_glob.winsize.ws_col) - command_line->scrolled_lines;
	research_nb_lines = get_research_nb_lines(command_line);
	i = cursor_y;
	return (process_get_down_from_command(i, full_y, cursor_y,
		research_nb_lines));
}
