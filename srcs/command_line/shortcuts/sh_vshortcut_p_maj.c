/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_p_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:37:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_p_maj.c
**
**  paste the content of the clipboard before the cursor
*/

int		sh_vshortcut_p_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	int nb_chars;

	(void)dummy;
	(void)dummy_2;
	if (!command_line->clipboard)
		return (SUCCESS);
	nb_chars = ft_strlen_utf8(command_line->clipboard);
	if (ft_substitute_dy_str(command_line->dy_str, command_line->clipboard,
		command_line->current_index, 0) != SUCCESS)
		return (FAILURE);
	command_line->current_index += ft_strlen(command_line->clipboard);
	command_line->nb_chars += nb_chars;
	render_command_line(command_line, nb_chars, 1);
	return (0);
}
