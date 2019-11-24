/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:47:33 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 19:50:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_main_init_vars:
**	Create a t_dy_tab used to store shell variables.
**	It also initialize some shell special parameters :
**		$ (bonus), ?
**	If any error occur, every locally allocated memory is free.
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS
*/

int			sh_main_init_vars(t_shell *shell)
{
	pid_t	pid;
	char	*buff;

	if (!(shell->vars = ft_dy_tab_new(10)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_vars"));
	if (ft_dy_tab_add_str(shell->vars, "?=0"))
	{
		shell->ret_value = 0;
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_vars (1)"));
	}
	if (ft_dy_tab_add_str(shell->vars, "#=0"))
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_vars (2)"));
	if (BONUS_DOLLAR_VARIABLE)
	{
		pid = getpid();
		if (!(buff = ft_itoa(pid)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_vars (3)"));
		if (sh_vars_assign_key_val(NULL, shell->vars, "$", buff) == FAILURE)
			return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_vars (4)"));
		free(buff);
	}
	return (SUCCESS);
}
