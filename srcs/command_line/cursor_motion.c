/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:45:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/06 11:19:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	go_right(int right)
{
	char		*str;
	int			i;

	str = tgetstr("nd", NULL);
	i = 0;
	while (i < right)
	{
		tputs(str, 1, putchar_int);
		i++;
	}
}

void	go_up_left(int up)
{
	char		*str;
	int			i;

	str = tgetstr("up", NULL);
	i = 0;
	while (i < up)
	{
		tputs(str, 1, putchar_int);
		i++;
	}
	str = tgetstr("cr", NULL);
	tputs(str, 1, putchar_int);
}

int		go_up_to_prompt(int width, int cursor)
{
	char		*str;
	int			val;
	int			i;

	str = tgetstr("up", NULL);
	i = 0;
	ft_dprintf(0, " ");
	val = ((get_true_cursor_pos_prev_prompt(cursor)) / width)
		- g_glob.command_line.scrolled_lines;
	while (i < val)
	{
		tputs(str, 1, putchar_int);
		i++;
	}
	str = tgetstr("cr", NULL);
	tputs(str, 1, putchar_int);
	return (i);
}
