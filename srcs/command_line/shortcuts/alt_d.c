/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:57:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 16:57:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_alt_d(t_command_line *command_line)
{
	int motion_index;
	int ret;

	command_line->count.value = 1;
	motion_index = sh_vs_motion_e_readline(command_line, 0);
	ret = sh_save_command_line(command_line);
	if (ret != SUCCESS)
		return (ret);
	else
		return (sh_vshortcut_d(command_line, motion_index, E_MOTION_IN));
}
