/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_shift_horizontal.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:41:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/21 15:19:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_process_shift_right(t_command_line *c_line,
			t_word *word, int *index)
{
	if (populate_word_by_index(c_line->dy_str->str, *index, word) != SUCCESS)
		return (FAILURE);
	if (word->len)
	{
		c_line->current_index += word->len - word->index_byte_offset + 1;
		render_command_line(c_line,
				word->utf8_len - word->index_char_offset + 1, 1);
		return (ft_del_turn_char(&word->str, SUCCESS));
	}
	ft_strdel(&word->str);
	while (*index < (int)c_line->dy_str->current_size)
	{
		if (populate_word_by_index(c_line->dy_str->str, *index, word)
				!= SUCCESS)
			return (FAILURE);
		if (word->len)
			break ;
		else
			ft_strdel(&word->str);
		*index += 1;
	}
	return (3);
}

int		process_shift_right(t_command_line *c_line)
{
	int		index;
	t_word	word;
	int		ret;

	index = c_line->current_index + 1;
	if ((ret = process_process_shift_right(c_line, &word, &index)) != 3)
	{
		replace_cursor_vim_legal(c_line);
		return (ret);
	}
	render_command_line(c_line, index - c_line->current_index - 1, 1);
	c_line->current_index = index - 1;
	replace_cursor_vim_legal(c_line);
	return (ft_del_turn_char(&word.str, SUCCESS));
}

int		process_process_shift_left(t_command_line *command_line,
			t_word *word, int *index)
{
	if (populate_word_by_index(command_line->dy_str->str, *index, word)
		!= SUCCESS)
		return (FAILURE);
	if (word->len)
	{
		command_line->current_index -= word->index_byte_offset;
		render_command_line(command_line, -word->index_char_offset, 1);
		return (ft_del_turn_char(&word->str, SUCCESS));
	}
	else
		ft_strdel(&word->str);
	while (*index > 0)
	{
		if (populate_word_by_index(command_line->dy_str->str, *index, word)
			!= SUCCESS)
			return (FAILURE);
		if (word->len)
			break ;
		else
			ft_strdel(&word->str);
		*index -= 1;
	}
	return (3);
}

int		process_shift_left(t_command_line *command_line)
{
	int		index;
	t_word	word;
	int		ret;

	index = command_line->current_index;
	if ((ret = process_process_shift_left(command_line, &word, &index)) != 3)
		return (ret);
	render_command_line(command_line,
		-(command_line->current_index - index), 1);
	command_line->current_index = index;
	return (ft_del_turn_char(&word.str, SUCCESS));
}
