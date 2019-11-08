/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:05:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/08 19:05:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	process_print_command_line(t_command_line *command_line,
			int empty_space)
{
	char			*str;
	int				index;
	t_utf8_copier	c;
	char			*tmp_str;

	populate_min_max_selection(command_line, &c.min, &c.max);
	if (!(str = (char *)malloc((4 * g_glob.winsize.ws_row *
			g_glob.winsize.ws_col) + 1)))
		return ;
	index = get_command_line_starting_index(command_line);
	c.i = index;
	c.nb_chars = 0;
	c.len = ft_strlen(&command_line->dy_str->str[index]);
	c.j = 0;
	while (command_line->dy_str->str[c.i]
		&& c.nb_chars < empty_space - ft_strlen_utf8(ELIPTIC_COMMAND_LINE))
		process_copy_utf8_char(str, command_line, index, &c);
	copy_last_part_of_command_line(command_line, &c, index, str);
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
		empty_space -= get_research_nb_lines(command_line)
			* g_glob.winsize.ws_col;
	process_print_command_line(command_line, empty_space);
}
