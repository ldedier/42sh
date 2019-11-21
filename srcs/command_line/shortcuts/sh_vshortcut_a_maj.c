/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_a_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:15:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_a_maj.c
**
** go to the end of the command line and get into insert mode
*/

int		sh_vshortcut_a_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	int ret;
	int i;
	int nb_chars;

	(void)dummy;
	(void)dummy_2;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	nb_chars = 0;
	i = command_line->current_index;
	while (i < (int)command_line->dy_str->current_size)
	{
		if ((ret = get_char_len(command_line->current_index,
				(unsigned char *)command_line->dy_str->str)) == -1)
		{
			return (FAILURE);
		}
		i += ret;
		nb_chars++;
	}
	render_command_line(command_line, nb_chars, 1);
	command_line->current_index = command_line->dy_str->current_size;
	return (SUCCESS);
}
