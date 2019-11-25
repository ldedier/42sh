/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 06:15:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_command_line_prefix_len(t_command_line *command_line)
{
	if (command_line->scrolled_lines)
		return (ft_strlen_utf8(ELIPTIC_COMMAND_LINE));
	else
		return (ft_strlen_utf8(command_line->prompt));
}

/*
** cursor_inc: tells the cursor movement to execute within the render of the
** command_line
*/

int		render_command_line(t_command_line *command_line,
			int cursor_inc, int print_choices)
{
	char	*str;
	int		ret;

	if (!isatty(0) || !command_line || g_glob.winsize.ws_row <= 1)
	{
		g_glob.cursor += cursor_inc;
		return (SUCCESS);
	}
	str = tgetstr("vi", NULL);
	tputs(str, 1, putchar_int);
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	sh_scroll_command_line(command_line, g_glob.cursor, cursor_inc);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	ret = 0;
	if (print_pre_command_line(command_line, &ret))
		return (ret);
	print_command_line(command_line);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	if (print_after_command_line(command_line, print_choices) != SUCCESS)
		return (FAILURE);
	str = tgetstr("ve", NULL);
	tputs(str, 1, putchar_int);
	return (SUCCESS);
}
