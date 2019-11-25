/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 19:54:46 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 00:48:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char	*get_research_title(t_command_line *command_line)
{
	if (command_line->searcher.unsuccessful == 0)
		return (UNSUCCESS_RSRCH);
	else
		return (SUCCESS_RSRCH);
}

int			get_research_nb_lines_n(t_command_line *command_line, int n)
{
	if (command_line->searcher.active)
		return ((((n + ft_strlen(get_research_title(command_line))
				+ 1) - 1) / g_glob.winsize.ws_col) + 1);
	else
		return (0);
}

int			get_research_nb_lines(t_command_line *command_line)
{
	if (command_line->searcher.active)
		return ((((ft_strlen_utf8(command_line->searcher.dy_str->str)
			+ ft_strlen(get_research_title(command_line))
				+ 1) - 1) / g_glob.winsize.ws_col) + 1);
	else
		return (0);
}

int			render_research(t_command_line *command_line)
{
	int		nb_visible_lines;
	char	title[100];

	ft_strcpy(title, get_research_title(command_line));
	ft_printf("%s%s_", title, command_line->searcher.dy_str->str);
	nb_visible_lines = ((ft_strlen_utf8(command_line->searcher.dy_str->str)
		+ ft_strlen(title) + 1) - 1) / g_glob.winsize.ws_col;
	go_up_left(nb_visible_lines);
	return (SUCCESS);
}
