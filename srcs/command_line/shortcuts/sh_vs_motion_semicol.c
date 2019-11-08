/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_semicol.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:13:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_semicol.c
**
**	repeat last ft command, ignoring the count value
*/

int		sh_vs_motion_semicol(t_command_line *command_line, char dummy)
{
	(void)dummy;
	if (!command_line->last_ft_command.motion)
		return (command_line->current_index);
	command_line->count.value = 1;
	command_line->last_ft_command.locked = 1;
	return (command_line->last_ft_command.motion(command_line,
		command_line->last_ft_command.c));
}
