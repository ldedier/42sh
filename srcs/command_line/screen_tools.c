/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 11:30:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/20 15:51:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		putchar_int(int i)
{
	ft_putchar_fd(i, g_glob.command_line.fd);
	return (0);
}

int		process_clear(t_command_line *command_line)
{
	char *str;

	str = tgetstr("cl", NULL);
	tputs(str, 1, putchar_int);
	render_command_line(command_line, 0, 1);
	return (0);
}
