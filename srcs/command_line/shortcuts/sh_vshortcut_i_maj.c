/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_i_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:36:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_i_maj.c
**
**	go to the start of the command and get into insert mode
*/

int		sh_vshortcut_i_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	(void)dummy;
	(void)dummy_2;
	(void)command_line;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line) != SUCCESS)
		return (FAILURE);
	command_line->current_index = 0;
	render_command_line(command_line, -g_glob.cursor, 1);
	return (SUCCESS);
}
