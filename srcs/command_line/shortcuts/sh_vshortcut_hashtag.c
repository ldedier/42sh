/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_hashtag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/20 12:10:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_hashtag.c
**	
**	comment current command line and send it to execution
*/

int		sh_vshortcut_hashtag(t_command_line *command_line, int dummy, int dummy_2)
{
	int ret;

	(void)dummy;
	(void)dummy_2;
	(void)command_line;
	if (ft_substitute_dy_str(command_line->dy_str, "#", 0, 0))
		return (FAILURE);
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	get_down_from_command(command_line);
	ret = execute_command(command_line->shell, command_line->dy_str->str, 1);
	flush_command_line(command_line);
	render_command_line(command_line, -g_glob.cursor, 1);
	return (ret);
}
