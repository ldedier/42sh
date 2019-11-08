/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_j.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:36:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_j.c
**
**	replace the command_line with the counth previous entry
*/

int		sh_vshortcut_j(t_command_line *command_line, int dummy, int dummy_2)
{
	int ret;

	(void)dummy;
	(void)dummy_2;
	if ((ret = process_history_down(command_line->shell, command_line,
		command_line->count.value, 1)) == FAILURE)
		return (FAILURE);
	replace_cursor_vim_legal(command_line);
	return (ret);
}
