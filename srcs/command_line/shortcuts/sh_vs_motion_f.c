/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:12:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_f.c
**
**	go to the counth occurence of c starting from command line current index
*/

int		sh_vs_motion_f(t_command_line *command_line, char c)
{
	size_t	i;
	int		found_char;
	int		last_found;

	if (!command_line->last_ft_command.locked)
	{
		command_line->last_ft_command.c = c;
		command_line->last_ft_command.motion = &sh_vs_motion_f;
	}
	else
		command_line->last_ft_command.locked = 0;
	last_found = command_line->current_index;
	i = command_line->current_index + 1;
	found_char = 0;
	while (i < command_line->dy_str->current_size)
	{
		if (command_line->dy_str->str[i] == c)
		{
			last_found = i;
			if (++found_char == command_line->count.value)
				return (i);
		}
		i++;
	}
	return (last_found);
}
