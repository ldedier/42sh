/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_caret.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:03:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_caret.c
**
** go to the first non white character of the line
** if all characters are blanks, go to the last character
*/

int		sh_vs_motion_caret(t_command_line *command_line, char dummy)
{
	size_t i;

	(void)dummy;
	i = 0;
	while (i < command_line->dy_str->current_size)
	{
		if (!ft_iswhite(command_line->dy_str->str[i]))
			return (i);
		i++;
	}
	return (i);
}
