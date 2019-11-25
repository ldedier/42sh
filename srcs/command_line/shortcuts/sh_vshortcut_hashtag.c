/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_hashtag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 07:43:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_hashtag.c
**
**	comment current command line and send it to execution
*/

int		sh_vshortcut_hashtag(t_command_line *command_line, int dummy,
		int dummy_2)
{
	(void)dummy;
	(void)dummy_2;
	if (ft_substitute_dy_str(command_line->dy_str, "#", 0, 0))
		return (FAILURE);
	command_line->current_index += 1;
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 1, 1);
	if (ioctl(g_term_fd, TIOCSTI, "\n") == -1)
		return (FAILURE);
	return (SUCCESS);
}
