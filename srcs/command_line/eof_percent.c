/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:25:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/20 15:56:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_eof_delimiter(void)
{
	char *res;

	res = tgetstr("ce", NULL);
	tputs(res, 1, putchar_int);
	res = tgetstr("mr", NULL);
	tputs(res, 1, putchar_int);
	ft_dprintf(g_glob.command_line.fd, "%%");
	res = tgetstr("me", NULL);
	tputs(res, 1, putchar_int);
}

int		sh_add_eof(int interrupted)
{
	int		i;
	char	*res;

	if (!interrupted)
	{
		print_eof_delimiter();
		i = 0;
		while (i < g_glob.winsize.ws_col - 1)
		{
			ft_dprintf(g_glob.command_line.fd, " ");
			i++;
		}
		res = tgetstr("cr", NULL);
		tputs(res, 1, putchar_int);
		res = tgetstr("ce", NULL);
		tputs(res, 1, putchar_int);
	}
	return (SUCCESS);
}
