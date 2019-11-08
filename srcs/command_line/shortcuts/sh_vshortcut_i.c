/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:35:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_i.c
**
**	go into insert mode
*/

int		sh_vshortcut_i(t_command_line *command_line, int dummy, int dummy_2)
{
	(void)dummy;
	(void)dummy_2;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (0);
}
