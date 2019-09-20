/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/03/28 11:02:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_p.c
**
**	paste the content of the clipboard after the cursor
*/

int		sh_vshortcut_p(t_command_line *command_line, int dummy, int dummy_2)
{
	int nb_chars;

	(void)dummy;
	(void)dummy_2;
	if (!command_line->clipboard)
		return (SUCCESS);
	if (ft_substitute_dy_str(command_line->dy_str,
		 command_line->clipboard, ft_min(command_line->current_index + 1, command_line->dy_str->current_size), 0))
	{
		return (FAILURE);
	}
	nb_chars = ft_strlen_utf8(command_line->clipboard);
	command_line->current_index += ft_strlen(command_line->clipboard);
	command_line->nb_chars += nb_chars;
	render_command_line(command_line, nb_chars, 1);
	return (SUCCESS);
}
