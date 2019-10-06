/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/12 19:18:38 by ldedier          ###   ########.fr       */
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

	to_go_up = 0;
	if (print_choices && command_line->autocompletion.active)
	{
		render_choices(command_line, &to_go_up);
		if (to_go_up > 0)
		{
			go_up_left(to_go_up);
			replace_cursor_on_index();
		}
	}
	else if (command_line->searcher.active)
	{
		to_go_up = get_down_from_command(command_line);
	//	ft_dprintf(2, "togoup: %d\n", to_go_up);
		if (render_research(command_line))
			return (FAILURE);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	return (SUCCESS);
}

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

void	process_termcaps_through_copy(t_command_line *command_line,
			t_utf8_copier *c, char *str, char *capability)
{
	char *tmp_str;

	tmp_str = tgetstr(capability, NULL);
	str[c->j] = 0;
	ft_dprintf(command_line->fd, "%s", str);
	c->j = 0;
	tputs(tmp_str, 1, putchar_int);
}

void	process_termcaps_through_utf8_copy(char *str,
			t_command_line *command_line, t_utf8_copier *c)
{
	if (command_line->mode == E_MODE_VISUAL 
		&& command_line->pinned_index != -1 && c->min != c->max)
	{
		if (c->i == c->min)
			process_termcaps_through_copy(command_line, c, str, "mr");
		if (c->i == c->max)
			process_termcaps_through_copy(command_line, c, str, "me");
	}
	else if (command_line->searcher.active
		&& !command_line->searcher.unsuccessful
			&& ft_strcmp(command_line->dy_str->str, ""))
	{
		if (c->i == command_line->searcher.match_index)
			process_termcaps_through_copy(command_line, c, str, "us");
		else if (c->i == (int)(command_line->searcher.match_index
			+ ft_strlen(command_line->searcher.dy_str->str)))
			process_termcaps_through_copy(command_line, c, str, "me");
	}
}

void	process_copy_utf8_char(char *str,
			t_command_line *command_line, int index, t_utf8_copier *c)
{
	int		tmp;

	process_termcaps_through_utf8_copy(str, command_line, c);
	tmp = get_char_len2(0, c->len,
		(unsigned char *)&command_line->dy_str->str[c->i - index]);
	ft_strncpy(&str[c->j], &command_line->dy_str->str[c->i], tmp);
	c->len -= tmp;
	c->i += tmp;
	c->j += tmp;
	c->nb_chars++;
}

void	process_print_command_line(t_command_line *command_line,
			int empty_space)
{
	char			*str;
	int				index;
	t_utf8_copier	c;
	char			*tmp_str;

	populate_min_max_selection(command_line, &c.min, &c.max);
	if (!(str = malloc((4 * g_glob.winsize.ws_row * g_glob.winsize.ws_col) + 1 )))
		return ;
	index = get_command_line_starting_index(command_line);
	c.i = index;
	c.nb_chars = 0;
	c.len = ft_strlen(&command_line->dy_str->str[index]);
	c.j = 0;
	while (command_line->dy_str->str[c.i]
		&& c.nb_chars < empty_space - ft_strlen_utf8(ELIPTIC_COMMAND_LINE))
	{
		process_copy_utf8_char(str, command_line, index, &c);
	}
	if (ft_strlen_utf8(&command_line->dy_str->str[c.i])
		<= ft_strlen_utf8(ELIPTIC_COMMAND_LINE))
	{
		while (command_line->dy_str->str[c.i])
		{
			process_copy_utf8_char(str, command_line, index, &c);
		}
	}
	else
	{
		ft_strcpy(&str[c.j], ELIPTIC_COMMAND_LINE);
		c.j += ft_strlen(ELIPTIC_COMMAND_LINE);
	}
	str[c.j] = 0;
	ft_dprintf(command_line->fd, "%s", str);
	free(str);
	tmp_str = tgetstr("me", NULL);
	tputs(tmp_str, 1, putchar_int);
}

void	print_command_line(t_command_line *command_line)
{
	int empty_space;

	if (command_line->scrolled_lines)
		empty_space = (g_glob.winsize.ws_col * (g_glob.winsize.ws_row - 1))
			+ g_glob.winsize.ws_col - ft_strlen_utf8(ELIPTIC_COMMAND_LINE) - 1;
	else
		empty_space = (g_glob.winsize.ws_col * (g_glob.winsize.ws_row - 1))
			+ g_glob.winsize.ws_col
				- ft_strlen_utf8(g_glob.command_line.prompt) - 1;
	if (command_line->searcher.active)

	{
	//	ft_dprintf(2, "research nb lines: %d\n", get_research_nb_lines(command_line));
		empty_space -= get_research_nb_lines(command_line) * g_glob.winsize.ws_col;
	}
	process_print_command_line(command_line, empty_space);
}

int		get_command_line_prefix_len(t_command_line *command_line)
{
	if (command_line->scrolled_lines)
		return (ft_strlen_utf8(ELIPTIC_COMMAND_LINE));
	else
		return (ft_strlen_utf8(command_line->prompt));
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

int		sh_scroll_command_line(t_command_line *command_line,
			int cursor, int cursor_inc)
{
	int true_cursor;
	int current_screen_line;
	int target_screen_line;
	int ret;
	int	research_nb_lines;

	research_nb_lines = get_research_nb_lines(command_line);
	true_cursor = get_true_cursor_pos_prev_prompt(cursor);
	//ft_dprintf(2, "research_nb_lines: %d\n", research_nb_lines);
	// ft_dprintf(2, "scrolled lines:%d\ntarget:%d 
	// (+%d)\ncurrent:%d\nrow:%d\n\n", command_line->scrolled_lines, 
	// target_screen_line, cursor_inc, current_screen_line, g_glob.winsize.ws_row);
	
	//scroll with dimensions first.

	//si ws_row > necessaire et que on est a la fin => nb_scrolled -= chepa
	
	while (!should_elipse_end(command_line, command_line->scrolled_lines)
		&& command_line->scrolled_lines
		&& g_glob.winsize.ws_row - research_nb_lines
			> command_line_nb_rows(command_line))
	{
		command_line->scrolled_lines--;
	}
	target_screen_line = ((true_cursor + cursor_inc) / g_glob.winsize.ws_col)
		- command_line->scrolled_lines;
	current_screen_line = (true_cursor / g_glob.winsize.ws_col)
		- command_line->scrolled_lines;
	if (target_screen_line < 1)
	{
		if (command_line->scrolled_lines + target_screen_line > 0)
			ret = target_screen_line - 1;
		else
			ret = target_screen_line;
	}
	else if (target_screen_line >= g_glob.winsize.ws_row - 1 - research_nb_lines)
	{
		if (should_elipse_end(command_line, command_line->scrolled_lines +
			target_screen_line - g_glob.winsize.ws_row + 1 + research_nb_lines))
			ret = target_screen_line - g_glob.winsize.ws_row + research_nb_lines + 2;
		else
			ret = target_screen_line - g_glob.winsize.ws_row + research_nb_lines + 1;
	}
	else
		return (0);
	command_line->scrolled_lines += ret;
	return (ret);
}

void	check_selection(t_command_line *command_line)
{
	int		min;
	int		max;
	int		index;
	char	*tmp_str;

	if (command_line->mode == E_MODE_VISUAL && command_line->pinned_index != -1)
	{
		index = get_command_line_starting_index(command_line);
		populate_min_max_selection(command_line, &min, &max);
		if (min < index)
		{
			tmp_str = tgetstr("mr", NULL);
			tputs(tmp_str, 1, putchar_int);
		}
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
	int		ret;

	if (!isatty(0) || !command_line)
		return (SUCCESS);
	go_up_to_prompt(g_glob.winsize.ws_col, g_glob.cursor);
	ret = sh_scroll_command_line(command_line, g_glob.cursor, cursor_inc);
	str = tgetstr("cd", NULL);
	tputs(str, 1, putchar_int);
	if (command_line->scrolled_lines && g_glob.winsize.ws_row <= 2)
	{
		ft_dprintf(command_line->fd, "<...>");
		return (SUCCESS);
	}
	if (!command_line->scrolled_lines)
		ft_dprintf(command_line->fd, "%s%s%s%s",
			BOLD, CYAN, g_glob.command_line.prompt, EOC);
	else
	{
		check_selection(command_line);
		ft_dprintf(command_line->fd, "%s", ELIPTIC_COMMAND_LINE);
	}
	print_command_line(command_line);
	g_glob.cursor += cursor_inc;
	replace_cursor_after_render();
	(void)print_choices;
	if (print_after_command_line(command_line, print_choices) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
