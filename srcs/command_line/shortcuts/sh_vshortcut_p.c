/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:42:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_p.c
**
**	paste the content of the clipboard after the cursor
*/

char	*get_string_to_paste(t_command_line *command_line)
{
	int		i;
	char	*res;
	int		cp_len;

	cp_len = ft_strlen(command_line->clipboard);
	if (!(res = ft_strnew(cp_len * command_line->count.value)))
		return (sh_perrorn(SH_ERR1_MALLOC, "get_string_to_paste"));
	i = 0;
	while (i < command_line->count.value)
	{
		ft_strcpy(&res[i * cp_len], command_line->clipboard);
		i++;
	}
	return (res);
}

int		sh_vshortcut_process_p(t_command_line *command_line, char *to_paste)
{
	int		nb_chars;

	nb_chars = ft_strlen_utf8(to_paste);
	command_line->current_index += ft_strlen(to_paste);
	if (command_line->current_index > 0
		&& command_line->current_index
		== (int)command_line->dy_str->current_size)
	{
		command_line->current_index =
			get_left_w_char_index_dy_str(command_line->dy_str,
				command_line->current_index);
		nb_chars--;
	}
	command_line->nb_chars += nb_chars;
	render_command_line(command_line, nb_chars, 1);
	free(to_paste);
	return (SUCCESS);
}

int		sh_vshortcut_p(t_command_line *command_line, int dummy, int dummy_2)
{
	char	*to_paste;

	(void)dummy;
	(void)dummy_2;
	if (!command_line->clipboard)
		return (SUCCESS);
	if (!(to_paste = get_string_to_paste(command_line)))
		return (FAILURE);
	if (ft_substitute_dy_str(command_line->dy_str, to_paste,
		ft_min(command_line->current_index + 1,
			command_line->dy_str->current_size), 0))
	{
		return (FAILURE);
	}
	return (sh_vshortcut_process_p(command_line, to_paste));
}
