/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_e_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:11:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_e_maj.c
**
**	go to the end of the counth bigword
**	starting from command_line->current_index
*/

int		sh_vs_motion_e_maj(t_command_line *command_line, char dummy)
{
	int		i;
	char	prev_type;
	int		new_type;
	int		nb_word_end;

	(void)dummy;
	if (command_line->current_index == (int)command_line->dy_str->current_size)
		return (command_line->current_index);
	prev_type = get_char_type_bword(command_line,
			command_line->current_index + 1);
	nb_word_end = 0;
	i = command_line->current_index + 1;
	while (i < (int)command_line->dy_str->current_size)
	{
		new_type = get_char_type_bword(command_line, i);
		if (new_type != prev_type && prev_type != ' ')
		{
			if (++nb_word_end == command_line->count.value)
				return (i - 1);
		}
		prev_type = new_type;
		i++;
	}
	return (command_line->dy_str->current_size);
}
