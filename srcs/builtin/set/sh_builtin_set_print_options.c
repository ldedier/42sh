/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set_print_options.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:59:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 16:03:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	print_builtin_usage(void)
{
	sh_perror("set [-o option] [+o option]", NULL);
}

int		print_options_minus(t_shell *shell)
{
	(void)shell;
	if (g_glob.command_line.edit_style == E_EDIT_STYLE_VIM)
		ft_printf("vim\t\ton\n");
	else
		ft_printf("vim\t\toff\n");
	return (SUCCESS);
}

int		print_options_plus(t_shell *shell)
{
	(void)shell;
	ft_printf("set ");
	if (g_glob.command_line.edit_style == E_EDIT_STYLE_VIM)
		ft_printf("-o vim\n");
	else
		ft_printf("+o vim\n");
	return (SUCCESS);
}
