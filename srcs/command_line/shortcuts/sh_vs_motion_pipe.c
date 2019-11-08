/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:13:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_pipe.c
**
**	go to the counth character (starting from 1)
*/

int		sh_vs_motion_pipe(t_command_line *command_line, char dummy)
{
	int tmp;
	int res;
	int nb_chars;

	(void)dummy;
	nb_chars = 0;
	res = 0;
	while (res < (int)command_line->dy_str->current_size
			&& nb_chars < command_line->count.value - 1)
	{
		if ((tmp = get_char_len(res,
			(unsigned char *)command_line->dy_str->str)) == -1)
		{
			return (FAILURE);
		}
		res += tmp;
		nb_chars++;
	}
	return (res);
}
