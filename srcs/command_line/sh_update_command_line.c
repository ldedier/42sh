/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_update_command_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:03:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/08 17:43:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	update_command_line_end(t_command_line *command_line)
{
	command_line->current_index = command_line->dy_str->current_size;
	command_line->nb_chars = ft_strlen_utf8(command_line->dy_str->str);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
}

static void	update_command_line_start(t_command_line *command_line)
{
	command_line->current_index = 0;
	command_line->nb_chars = ft_strlen_utf8(command_line->dy_str->str);
	render_command_line(command_line, -g_glob.cursor, 1);
}

void		update_command_line_index(t_command_line *command_line, int index)
{
	int nb_chars;
	int len;
	int i;

	i = 0;
	len = ft_strlen(command_line->dy_str->str);
	nb_chars = 0;
	while (i < index)
	{
		i += get_char_len2(i, len, (unsigned char *)command_line->dy_str->str);
		nb_chars++;
	}
	command_line->current_index = i;
	command_line->nb_chars = nb_chars;
	render_command_line(command_line, -g_glob.cursor + nb_chars, 1);
}

void		update_command_line(t_command_line *command_line, int start)
{
	if (start)
		update_command_line_start(command_line);
	else
		update_command_line_end(command_line);
}
