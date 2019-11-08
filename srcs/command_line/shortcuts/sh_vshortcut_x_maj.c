/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_x_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:31:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_x_maj.c
**
**	delete the counth previous character before the cursor index
**	and save it in the clipboard
*/

void	go_back_count_characters(t_command_line *command_line,
			int *index, int *len, int *nb_chars)
{
	int res;

	*index = command_line->current_index;
	*nb_chars = 0;
	*len = 0;
	while (*index > 0 && *nb_chars < command_line->count.value)
	{
		res = get_left_w_char_index_dy_str(command_line->dy_str, *index);
		*len += *index - res;
		*index = res;
		(*nb_chars)++;
	}
}

int		sh_vshortcut_x_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	int		i;
	int		nb_chars;
	int		len;

	(void)dummy;
	(void)dummy_2;
	go_back_count_characters(command_line, &i, &len, &nb_chars);
	command_line->current_index -= len;
	ft_strdel(&command_line->clipboard);
	if (!(command_line->clipboard =
		ft_strndup(&command_line->dy_str->str[command_line->current_index],
			len)))
	{
		return (FAILURE);
	}
	ft_substitute_dy_str(command_line->dy_str, "",
		command_line->current_index, len);
	command_line->nb_chars -= nb_chars;
	render_command_line(command_line, -nb_chars, 1);
	return (0);
}
