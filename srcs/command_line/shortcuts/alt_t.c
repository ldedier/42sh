/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:02:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 17:56:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int				sh_vs_motion_b_readline_alt(t_command_line *command_line,
		int nb_words)
{
	int		i;
	char	prev_type;
	int		new_type;
	int		nb_word_start;

	if (command_line->current_index == 0)
		return (command_line->current_index);
	prev_type = get_char_type_word_readline(command_line,
			command_line->current_index);
	nb_word_start = 0;
	i = command_line->current_index;
	while (i >= 0)
	{
		new_type = get_char_type_word_readline(command_line, i);
		if (new_type != prev_type && prev_type != ' ')
		{
			if (++nb_word_start == nb_words)
				return (i + 1);
		}
		prev_type = new_type;
		i--;
	}
	return (0);
}

static int		get_indexes(t_command_line *command_line, int *index_a,
		int *index_b)
{
	if (get_next_word_index_readline(command_line, index_b) != SUCCESS)
	{
		*index_a = sh_vs_motion_b_readline_alt(command_line, 2);
		*index_b = sh_vs_motion_b_readline_alt(command_line, 1);
	}
	else
		*index_a = sh_vs_motion_b_readline_alt(command_line, 1);
	if (*index_a == *index_b ||
			!ft_isalnum(command_line->dy_str->str[*index_a]))
		return (1);
	return (0);
}

static int		word_len(char *str, int index)
{
	int i;

	i = index;
	while (ft_isalnum(str[i]))
		i++;
	return (i - index);
}

static int		swap_words(t_command_line *command_line,
		int index_a, int index_b)
{
	int		len_a;
	int		len_b;
	char	*word_a_str;
	char	*space_str;
	int		add;

	len_a = word_len(command_line->dy_str->str, index_a);
	len_b = word_len(command_line->dy_str->str, index_b);
	if (!(word_a_str = ft_strnew(len_a)))
		return (FAILURE);
	ft_strncpy(word_a_str, &command_line->dy_str->str[index_a], len_a);
	if (!(space_str = ft_strnew(index_b - (index_a + len_a))))
		ft_free_turn(word_a_str, FAILURE);
	ft_strncpy(space_str, &command_line->dy_str->str[index_a + len_a],
			index_b - (index_a + len_a));
	ft_strncpy(&command_line->dy_str->str[index_a],
			&command_line->dy_str->str[index_b], len_b);
	add = len_b;
	ft_strncpy(&command_line->dy_str->str[index_a + add], space_str,
			index_b - (index_a + len_a));
	add += index_b - (index_a + len_a);
	ft_strncpy(&command_line->dy_str->str[index_a + add], word_a_str, len_a);
	free(word_a_str);
	free(space_str);
	return (SUCCESS);
}

/*
** transpose whole readline words
*/

int				process_alt_t(t_command_line *command_line)
{
	int index_a;
	int index_b;
	int motion_index;
	int ret;

	if (get_indexes(command_line, &index_a, &index_b))
		return (SUCCESS);
	if ((ret = sh_save_command_line(command_line)))
		return (ret);
	motion_index = index_b + word_len(command_line->dy_str->str, index_b) - 1;
	if (motion_index != (int)command_line->dy_str->current_size)
	{
		motion_index += get_char_len(motion_index,
				(unsigned char *)command_line->dy_str->str);
	}
	if (swap_words(command_line, index_a, index_b) != SUCCESS)
		return (sh_perror(SH_ERR1_MALLOC, "swap_words"));
	execute_motion(command_line, motion_index, 0);
	return (SUCCESS);
}
