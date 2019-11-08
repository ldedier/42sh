/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_s_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:42:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_s_maj.c
**
**	clear line and get into insert mode
*/

int		sh_vshortcut_s_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	(void)dummy;
	(void)dummy_2;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line) != SUCCESS)
		return (FAILURE);
	flush_command_line(command_line);
	render_command_line(command_line, -g_glob.cursor, 1);
	return (0);
}
