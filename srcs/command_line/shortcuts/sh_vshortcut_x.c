/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:30:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_x.c
**
**	delete the counth next character following the cursor index
**	and save it in the clipboard
*/

int		advance_count_characters(t_command_line *command_line,
			int *index, int *len, int *nb_chars)
{
	int	res;

	*nb_chars = 0;
	*len = 0;
	*index = command_line->current_index;
	while (*index < (int)command_line->dy_str->current_size
			&& *nb_chars < command_line->count.value)
	{
		if ((res = get_char_len(*index,
						(unsigned char *)command_line->dy_str->str)) == -1)
		{
			return (FAILURE);
		}
		*index += res;
		*len += res;
		(*nb_chars)++;
	}
	return (SUCCESS);
}

int		sh_vshortcut_x(t_command_line *command_line, int dummy, int dummy_2)
{
	int		i;
	int		nb_chars;
	int		len;

	(void)dummy;
	(void)dummy_2;
	if (advance_count_characters(command_line, &i, &len, &nb_chars) != SUCCESS)
		return (FAILURE);
	ft_strdel(&command_line->clipboard);
	if (!(command_line->clipboard =
		ft_strndup(&command_line->dy_str->str[command_line->current_index],
			len)))
	{
		return (sh_perror(SH_ERR1_MALLOC, "sh_vshortcut_x"));
	}
	if (ft_substitute_dy_str(command_line->dy_str, "",
		command_line->current_index, len))
	{
		return (FAILURE);
	}
	command_line->nb_chars -= nb_chars;
	render_command_line(command_line, 0, 1);
	return (0);
}
