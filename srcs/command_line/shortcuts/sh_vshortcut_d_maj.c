/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_d_maj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:33:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_d_maj.c
**
**	equivalent to d$
*/

int		sh_vshortcut_d_maj(t_command_line *command_line, int dummy, int dummy_2)
{
	(void)dummy;
	(void)dummy_2;
	return (sh_vshortcut_d(command_line,
		command_line->dy_str->current_size, E_MOTION_IN));
}
