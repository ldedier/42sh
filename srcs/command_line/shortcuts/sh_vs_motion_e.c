/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_e.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:10:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_e.c
**
**	go to the end of the counth word starting from command_line->current_index
*/

int		sh_vs_motion_e(t_command_line *command_line, char dummy)
{
	int		i;
	char	prev_type;
	int		new_type;
	int		nb_word_end;
	int		first;

	(void)dummy;
	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (command_line->current_index);
	prev_type = get_char_type_word(command_line, command_line->current_index);
	nb_word_end = 0;
	i = command_line->current_index;
	first = 1;
	while (++i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_word(command_line, i);
		if (new_type != prev_type && prev_type != ' ')
		{
			if (first == 0 && ++nb_word_end == command_line->count.value)
				return (i - 1);
		}
		first = 0;
		prev_type = new_type;
	}
	return (command_line->dy_str->current_size);
}

int		sh_vs_motion_e_readline(t_command_line *command_line, char dummy)
{
	int			i;
	char		prev_type;
	int			new_type;
	int			nb_word_end;

	(void)dummy;
	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (command_line->current_index);
	prev_type = get_char_type_word_readline(command_line,
		command_line->current_index);
	nb_word_end = 0;
	i = command_line->current_index;
	while (++i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_word_readline(command_line, i);
		if (new_type != prev_type && prev_type != ' ')
		{
			if (i != command_line->current_index + 1 &&
					++nb_word_end == command_line->count.value)
				return (i - 1);
		}
		prev_type = new_type;
	}
	return (command_line->dy_str->current_size);
}

int		get_next_word_index_readline(t_command_line *command_line, int *index)
{
	int		i;
	char	prev_type;
	int		new_type;

	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (ERROR);
	if ((prev_type = get_char_type_word_readline(command_line,
		command_line->current_index)) != ' ')
		return (ERROR);
	i = command_line->current_index + 1;
	while (i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_word_readline(command_line, i);
		if (new_type != prev_type && prev_type == ' ')
		{
			*index = i;
			return (SUCCESS);
		}
		prev_type = new_type;
		i++;
	}
	return (ERROR);
}

int		sh_vs_motion_e_readline_no_end(t_command_line *command_line, char dummy)
{
	int		i;
	char	prev_type;
	int		new_type;

	(void)dummy;
	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (command_line->current_index);
	prev_type = get_char_type_word_readline(command_line,
		command_line->current_index);
	i = command_line->current_index + 1;
	while (i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_word_readline(command_line, i);
		if (new_type != prev_type && prev_type != ' ')
			return (i - 1);
		prev_type = new_type;
		i++;
	}
	return (command_line->dy_str->current_size);
}
