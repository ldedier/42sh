/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:31:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_c.c
**
**	delete the characters between the current index and the motion
**	returned index, then get into insert mode before the deletion
*/

int		sh_vshortcut_c(t_command_line *command_line, int index, int special)
{
	if (index == command_line->current_index && !special)
		return (SUCCESS);
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	return (sh_vshortcut_d(command_line, index, special));
}
