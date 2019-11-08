/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_w_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:32:36 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char	get_char_type_bword(t_command_line *command_line, int index)
{
	char starting_char;

	starting_char = command_line->dy_str->str[index];
	if (ft_iswhite(starting_char))
		starting_char = ' ';
	else
		starting_char = 'a';
	return (starting_char);
}

/*
** sh_vs_motion_w_maj.c
**
**	go to the start of the counth next bigword
*/

int		sh_vs_motion_w_maj(t_command_line *command_line, char dummy)
{
	int		i;
	char	prev_type;
	int		new_type;
	int		nb_word_start;

	(void)dummy;
	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (command_line->current_index);
	prev_type = get_char_type_bword(command_line, command_line->current_index);
	nb_word_start = 0;
	i = command_line->current_index;
	while (i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_bword(command_line, i);
		if (new_type != ' ' && new_type != prev_type)
		{
			if (++nb_word_start == command_line->count.value)
				return (i);
		}
		prev_type = new_type;
		i++;
	}
	return (command_line->dy_str->current_size);
}
