/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:04:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 07:52:30 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

void	copy_last_part_of_command_line(t_command_line *command_line,
			t_utf8_copier *c, int index, char *str)
{
	if (ft_strlen_utf8(&command_line->dy_str->str[c->i])
			<= ft_strlen_utf8(ELIPTIC_COMMAND_LINE))
	{
		while (command_line->dy_str->str[c->i])
			process_copy_utf8_char(str, command_line, index, c);
	}
	else
	{
		ft_strcpy(&str[c->j], ELIPTIC_COMMAND_LINE);
		c->j += ft_strlen(ELIPTIC_COMMAND_LINE);
	}
	str[c->j] = 0;
}
