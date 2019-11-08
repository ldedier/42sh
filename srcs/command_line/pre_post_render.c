/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_command_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:40:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/08 19:08:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
		if (render_research(command_line))
			return (FAILURE);
		go_up_left(to_go_up);
		replace_cursor_on_index();
	}
	return (SUCCESS);
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

int		print_pre_command_line(t_command_line *command_line, int *ret)
{
	if (command_line->scrolled_lines && g_glob.winsize.ws_row <= 2)
	{
		ft_dprintf(command_line->fd, "<...>");
		*ret = SUCCESS;
		return (1);
	}
	if (!command_line->scrolled_lines)
		ft_dprintf(command_line->fd, "%s%s%s%s",
			BOLD, CYAN, g_glob.command_line.prompt, EOC);
	else
	{
		check_selection(command_line);
		ft_dprintf(command_line->fd, "%s", ELIPTIC_COMMAND_LINE);
	}
	return (0);
}
