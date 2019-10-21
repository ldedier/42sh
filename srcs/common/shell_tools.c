/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 13:59:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/10 00:49:30 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_reset_shell(int ret)
{
	if (tcsetattr(g_term_fd, TCSADRAIN, &g_glob.term_init) == -1)
		return (ATTR_ERROR);
	// if ((g_glob.term_init.c_lflag & ISIG) != 0)
	// 	ft_dprintf(2, "%sISIG SET\n%s", COLOR_BLUE, EOC);
	// else
	// 	ft_dprintf(2, "%sISIG USET\n%s", COLOR_BLUE, EOC);
	return (ret);
}

int		sh_set_shell_back(int ret)
{
	if (tcsetattr(g_term_fd, TCSADRAIN, &g_glob.term) == -1)
		return (ATTR_ERROR);
	// if ((g_glob.term.c_lflag & ISIG) == 0)
	// 	ft_dprintf(2, "%sISIG UNSET\n%s", COLOR_BLUE, EOC);
	// else
	// 	ft_dprintf(2, "%sISIG SET\n%s", COLOR_BLUE, EOC);
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
