/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vs_motion_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:12:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vs_motion_h.c
**
**  go to the counth character from the current index backward
*/

int		sh_vs_motion_h(t_command_line *command_line, char dummy)
{
	int len;
	int index;
	int nb_chars;

	(void)dummy;
	go_back_count_characters(command_line, &index, &len, &nb_chars);
	return (index);
}
