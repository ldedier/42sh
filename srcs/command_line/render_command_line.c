/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/02 18:53:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	render_command_researched(t_command_line *command_line)
{
	int		len;
	char	*str;

	ft_putnstr_fd(command_line->dy_str->str,
		command_line->searcher.match_index, command_line->fd);
	str = tgetstr("us", NULL);
	tputs(str, 1, putchar_int);
	ft_putstr_fd(command_line->searcher.dy_str->str, command_line->fd);
	str = tgetstr("ue", NULL);
	tputs(str, 1, putchar_int);
	len = ft_strlen(command_line->searcher.dy_str->str);
	ft_putstr_fd(&command_line->dy_str->str[command_line->searcher.match_index
		+ len], command_line->fd);
}

int		print_after_command_line(t_command_line *command_line,
		int print_choices)
{
	int to_go_up;

	if (print_choices && command_line->autocompletion.active)
	{
		to_go_up = get_down_from_command(command_line);
		render_choices(command_line);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	else if (command_line->searcher.active)
	{
		to_go_up = get_down_from_command(command_line);
		if (render_research(command_line))
			return (FAILURE);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	return (SUCCESS);
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

void	process_print_command_line(t_command_line *command_line,
			int empty_space)
{
	char	*str;
	int		i;
	int		index;
	int		len;
	int		nb_chars;
	int		tmp;

	if (!(str = malloc((4 * g_glob.winsize.ws_row * g_glob.winsize.ws_col) + 1)))
		return ;
	index = get_command_line_starting_index(command_line);
	i = index;
//	ft_dprintf(2, "%d %d\n", i, index);
	nb_chars = 0;
	len = ft_strlen(&command_line->dy_str->str[index]);
	while (command_line->dy_str->str[i] && nb_chars < empty_space)
	{
		tmp = get_char_len2(0, len,
			(unsigned char *)&command_line->dy_str->str[i - index]);
//		ft_dprintf(2, "index: %d\ni:%d\ntmp:%d\n\n", index, i, tmp);
		ft_strncpy(&str[i - index], &command_line->dy_str->str[i], tmp);
		len -= tmp;
		i += tmp;
		nb_chars++;
	}
	if (nb_chars >= empty_space)
	{
		ft_strcpy(&str[i - index], ELIPTIC_COMMAND_LINE);
		i += ft_strlen(ELIPTIC_COMMAND_LINE);
	}
	str[i - index] = 0;
	ft_dprintf(command_line->fd, str);
}

void	print_command_line(t_command_line *command_line)
{
	int empty_space;

	if (command_line->scrolled_lines)
		empty_space = (g_glob.winsize.ws_col * g_glob.winsize.ws_row - 1)
			+ g_glob.winsize.ws_col - ft_strlen_utf8(ELIPTIC_COMMAND_LINE);
	else
		empty_space = (g_glob.winsize.ws_col * g_glob.winsize.ws_row - 1)
			+ g_glob.winsize.ws_col - ft_strlen_utf8(g_glob.command_line.prompt);
	process_print_command_line(command_line, empty_space);
}

void	sh_scroll_command_line(t_command_line *command_line,
			int cursor, int cursor_inc)
{
	int true_cursor;
	int current_screen_line;
	int target_screen_line;

	true_cursor = get_true_cursor_pos_prev_prompt(cursor);
	current_screen_line = (true_cursor / g_glob.winsize.ws_col)
		- command_line->scrolled_lines;
	target_screen_line = ((true_cursor + cursor_inc) / g_glob.winsize.ws_col)
		- command_line->scrolled_lines;
//	 ft_dprintf(2, "scrolled lines:%d\ntarget:%d (+%d)\ncurrent:%d\nrow:%d\n\n", command_line->scrolled_lines, target_screen_line, cursor_inc, current_screen_line, g_glob.winsize.ws_row);
	if (target_screen_line >= g_glob.winsize.ws_row)
	{
		command_line->scrolled_lines +=
			target_screen_line - g_glob.winsize.ws_row + 1;
	}
	else if (target_screen_line < 0)
	{
		command_line->scrolled_lines += target_screen_line;
	}
}

/*
** cursor_inc: tells the cursor movement to execute within the render of the
** command_line
*/

int		render_command_line(t_command_line *command_line,
			int cursor_inc, int print_choices)
{
	char	*str;

	if (!isatty(0) || !command_line)
		return (SUCCESS);
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	sh_scroll_command_line(command_line, g_glob.cursor, cursor_inc);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	if (!command_line->scrolled_lines)
		ft_dprintf(command_line->fd, "%s%s%s%s",
			BOLD, CYAN, g_glob.command_line.prompt, EOC);
	else
		ft_dprintf(command_line->fd, "%s", ELIPTIC_COMMAND_LINE);
	/*
	if (command_line->mode == E_MODE_VISUAL)
		render_command_visual(command_line);
	else if (command_line->searcher.active
			&& !command_line->searcher.unsuccessful
				&& ft_strcmp(command_line->searcher.dy_str->str, ""))
		render_command_researched(command_line);
	else
	*/
//	ft_dprintf(command_line->fd, "%s", command_line->dy_str->str);
	//ft_dprintf(command_line->fd, "%s", command_line->dy_str->str);
	print_command_line(command_line);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	(void)print_choices;
//	if (print_after_command_line(command_line, print_choices) != SUCCESS)
//		return (FAILURE);
	return (SUCCESS);
}
