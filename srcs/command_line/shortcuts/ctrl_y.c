/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_y.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:54:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/25 19:54:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_ctrl_y(t_command_line *command_line)
{
	int ret;

	ret = sh_save_command_line(command_line);
	if (ret != SUCCESS)
		return (ret);
	else
		return (paste_current_index(command_line, command_line->clipboard));
}
