/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_w.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:56:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 16:56:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_w(t_command_line *command_line)
{
	int motion_index;
	int ret;

	command_line->count.value = 1;
	motion_index = sh_vs_motion_b_readline(command_line, 0);
	ret = sh_save_command_line(command_line);
	if (ret != SUCCESS)
		return (ret);
	else
		return (sh_vshortcut_d(command_line, motion_index, E_MOTION_EX));
}
