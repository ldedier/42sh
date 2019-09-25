/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_k.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:56:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 16:56:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_k(t_command_line *command_line)
{
	int motion_index;
	int ret;

	motion_index = sh_vs_motion_dollar(command_line, 0);
	ret = sh_save_command_line(command_line);
	if (ret != SUCCESS)
		return (ret);
	else
		return (sh_vshortcut_d(command_line, motion_index, E_MOTION_IN));
}
