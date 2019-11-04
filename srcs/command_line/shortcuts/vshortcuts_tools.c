/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshortcuts_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:47:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:01:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_get_single_char(char *c)
{
	int		ret;
	char	buffer[4];

	ret = read(0, buffer, 4);
	if (ret == -1)
		return (sh_perror(SH_ERR1_READ, "sh_get_single_char"));
	if (ret == 1)
		*c = buffer[0];
	else
		*c = -1;
	return (SUCCESS);
}

int		ft_clamp(int min, int val, int max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	return (val);
}

int		is_printable_utf8_byte(unsigned char c)
{
	return (c >= 32 && c <= 126 && !(c & 0b10000000));
}

int		get_inclusion(t_command_line *command_line,
			t_motion_inclusion inclusion)
{
	if ((inclusion == E_MOTION_COPY || inclusion == E_MOTION_INV)
		&& command_line->last_ft_command.motion)
	{
		if (command_line->last_ft_command.motion == &sh_vs_motion_t
				|| command_line->last_ft_command.motion == &sh_vs_motion_f)
		{
			return (inclusion == E_MOTION_COPY ? E_MOTION_IN : E_MOTION_EX);
		}
		else
			return (inclusion == E_MOTION_COPY ? E_MOTION_EX : E_MOTION_IN);
	}
	else
		return (inclusion);
}
