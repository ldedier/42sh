/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer_from_tables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 02:36:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/05 13:54:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	fill_buffer_from_tables(t_command_line *command_line,
			char *print_buffer, t_file ***tbl, int max_len)
{
	int		i;
	int		j;

	i = 0;
	while (i < command_line->autocompletion.nb_lines)
	{
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			fill_buffer_from_file(command_line,
				&print_buffer, tbl[i][j], max_len);
			j++;
			if (j < command_line->autocompletion.nb_cols)
				fill_buffer_padding(&print_buffer);
		}
		i++;
		if (i < command_line->autocompletion.nb_lines)
		{
			ft_strcpy(print_buffer, "\n");
			print_buffer += 1;
		}
	}
}

void	fill_buffer_partial_from_tables(t_command_line *command_line,
			char *print_buffer, t_file ***tbl, int max_len)
{
	int		i;
	int		j;
	int		limit;

	i = command_line->autocompletion.scrolled_lines;
	while (i <= (limit = command_line->autocompletion.scrolled_lines
			+ g_glob.winsize.ws_row - 1 - command_line_nb_rows(command_line)))
	{
		j = 0;
		while (j < command_line->autocompletion.nb_cols)
		{
			fill_buffer_from_file(command_line,
				&print_buffer, tbl[i][j], max_len);
			j++;
			if (j < command_line->autocompletion.nb_cols)
				fill_buffer_padding(&print_buffer);
		}
		i++;
		if (i < limit + 1)
		{
			ft_strcpy(print_buffer, "\n");
			print_buffer += 1;
		}
	}
}
