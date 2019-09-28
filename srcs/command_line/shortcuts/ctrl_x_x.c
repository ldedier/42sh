/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_x_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:57:54 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 16:57:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	process_ctrl_x_x(t_command_line *command_line)
{
	int mark_save;

	command_line->buffer.persistent = 0;
	mark_save = command_line->mark_index;
	command_line->mark_index = command_line->current_index;
	execute_motion(command_line, mark_save, 0);
}
