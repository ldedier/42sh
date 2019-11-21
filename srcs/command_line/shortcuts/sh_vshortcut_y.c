/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_y.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:28:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_y.c
**
**	yank all characters between the current index and the motion returned index
*/

int		sh_vshortcut_y(t_command_line *command_line, int index, int special)
{
	int min;
	int max;

	if (special == E_MOTION_SPECIAL)
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
	}
	else
	{
		if (index == command_line->current_index)
			return (SUCCESS);
		ft_strdel(&command_line->clipboard);
		if (special == E_MOTION_IN)
		{
			if (index > command_line->current_index)
				index = ft_min(index + 1, command_line->dy_str->current_size);
		}
		min = ft_min(index, command_line->current_index);
		max = ft_max(index, command_line->current_index);
		if (!(command_line->clipboard =
					ft_strndup(&command_line->dy_str->str[min], max - min)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_vshortcut_d"));
	}
	return (SUCCESS);
}
