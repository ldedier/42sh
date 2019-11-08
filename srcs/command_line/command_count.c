/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:20:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:30:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	add_digit(t_command_count *count, char c)
{
	int n;

	n = c - '0';
	if (!count->active)
	{
		count->tmp_value = n;
		count->active = 1;
	}
	else if (count->tmp_value >= 10000)
	{
		count->active = 0;
		count->tmp_value = 1;
	}
	else
	{
		count->tmp_value = count->tmp_value * 10 + c - '0';
		count->active = 1;
	}
}

int			add_digit_and_update(t_command_line *command_line, char c)
{
	add_digit(command_line->current_count, c);
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}
