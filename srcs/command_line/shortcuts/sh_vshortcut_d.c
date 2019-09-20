/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_d.c
**	
**	delete the characters between the current index and the motion
**	returned index
*/

int		sh_vshortcut_d(t_command_line *command_line, int index, int special)
{
	int nb_chars_diff;
	int min;
	int max;

	if (special)
	{
		if (command_line_copy_all(command_line) != SUCCESS)
			return (FAILURE);
		flush_command_line(command_line);
		render_command_line(command_line, -g_glob.cursor, 1);
	}
	else
	{
		if (index == command_line->current_index)
			return (SUCCESS);
		ft_strdel(&command_line->clipboard);
		min = ft_min(index, command_line->current_index);
		max = ft_max(index, command_line->current_index);
		if (!(command_line->clipboard =
			ft_strndup(&command_line->dy_str->str[min], max - min)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_vshortcut_d"));
		nb_chars_diff = ft_strnlen_utf8(&command_line->dy_str->str[min],
			max - min);
		ft_substitute_dy_str(command_line->dy_str, "", min, max - min);
		command_line->nb_chars -= nb_chars_diff;
		if (command_line->current_index > index)
			render_command_line(command_line, -nb_chars_diff, 1);
		else
			render_command_line(command_line, 0, 1);
		command_line->current_index -=
			ft_max(0, command_line->current_index - index);
	}
	return (SUCCESS);
}
