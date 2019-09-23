/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vim_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:19:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/21 17:19:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		replace_cursor_vim_legal(t_command_line *command_line)
{
	if (command_line->mode == E_MODE_COMMAND
		&& command_line->current_index > 0
			&& command_line->current_index
			== (int)command_line->dy_str->current_size)
	{
		command_line->current_index =
			get_left_w_char_index_dy_str(command_line->dy_str,
					command_line->current_index);
		render_command_line(command_line, -1, 1);
		return (1);
	}
	else
		return (0);
}
