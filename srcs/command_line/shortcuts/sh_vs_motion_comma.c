/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_comma.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:03:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_comma.c
**
**	repeat the last ft_command, reversing it (f->F), (t<->T)
**	also ignore the count value
*/

int		sh_vs_motion_comma(t_command_line *command_line, char dummy)
{
	char c;

	(void)dummy;
	if (!command_line->last_ft_command.motion)
		return (command_line->current_index);
	c = command_line->last_ft_command.c;
	command_line->last_ft_command.locked = 1;
	if (command_line->last_ft_command.motion == &sh_vs_motion_t)
		return (sh_vs_motion_t_maj(command_line, c));
	else if (command_line->last_ft_command.motion == &sh_vs_motion_t_maj)
		return (sh_vs_motion_t(command_line, c));
	else if (command_line->last_ft_command.motion == &sh_vs_motion_f_maj)
		return (sh_vs_motion_f(command_line, c));
	else
		return (sh_vs_motion_f_maj(command_line, c));
}
