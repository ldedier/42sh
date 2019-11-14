/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:59:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/14 10:47:10 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_reset_shell(int ret)
{
	if (tcsetattr(g_term_fd, TCSADRAIN, &g_glob.term_init) < 0)
	{
		sh_perror("Could not modify this terminal attributes",
				"sh_reset_shell");
		return (-1);
	}
	return (ret);
}

int		sh_set_shell_back(int ret)
{
	if (tcsetattr(g_term_fd, TCSADRAIN, &g_glob.term) < 0)
	{
		sh_perror("Could not modify this terminal attributes",
				"sh_set_shell_back");
		return (-1);
	}
	return (ret);
}

int		clear_all(void)
{
	char *res;

	if (!(res = tgetstr("cl", NULL)))
		return (-1);
	tputs(res, 1, putchar_int);
	return (0);
}
