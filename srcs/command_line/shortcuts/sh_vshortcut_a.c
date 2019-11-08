/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:15:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_a.c
**
**	go to the next character and get into insert mode
*/

int		sh_vshortcut_a(t_command_line *command_line, int dummy, int dummy_2)
{
	int ret;

	(void)dummy;
	(void)dummy_2;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	if (command_line->current_index < (int)command_line->dy_str->current_size)
	{
		if ((ret = get_char_len(command_line->current_index,
				(unsigned char *)command_line->dy_str->str)) == -1)
		{
			return (FAILURE);
		}
		command_line->current_index += ret;
		render_command_line(command_line, 1, 1);
	}
	else
		render_command_line(command_line, 0, 1);
	return (SUCCESS);
}
