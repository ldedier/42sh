/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:58:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 16:58:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_alt_f(t_command_line *command_line)
{
	int motion_index;

	command_line->count.value = 1;
	motion_index = sh_vs_motion_w_readline(command_line, 0);
	return (execute_motion(command_line, motion_index, 0));
}
