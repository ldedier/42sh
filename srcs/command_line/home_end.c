/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:42:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 17:00:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_end(t_command_line *command_line)
{
	process_cancel_autocompletion(command_line);
	command_line->current_index = command_line->dy_str->current_size;
	replace_cursor_vim_legal(command_line);
	render_command_line(command_line,
		command_line->nb_chars - g_glob.cursor, 1);
	return (SUCCESS);
}

int		process_start(t_command_line *command_line)
{
	process_cancel_autocompletion(command_line);
	command_line->current_index = 0;
	replace_cursor_vim_legal(command_line);
	render_command_line(command_line, -g_glob.cursor, 1);
	return (SUCCESS);
}
