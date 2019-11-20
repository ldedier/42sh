/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_save_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 03:00:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 03:01:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_env_save_restore_command_clean:
**	Delete assignment in env table that are not in saved_env table,
**	and delete empty assignments in env table.
**	Function used after restoring env in a command case.
*/

void		sh_env_save_restore_command_clean(t_context *context)
{
	int		i;
	char	**tbl;

	tbl = (char**)context->env->tbl;
	i = 0;
	while (tbl[i])
	{
		if (!ft_strchr(tbl[i], '='))
		{
			if (sh_verbose_exec())
				ft_dprintf(2, GREEN"deleted empty var : %s\n"EOC, tbl[i]);
			ft_dy_tab_suppr_index(context->env, i);
		}
		else if (sh_env_save_get_index(context->saved_env, tbl[i]) == -1)
		{
			if (sh_verbose_exec())
				ft_dprintf(2, GREEN"deleted old var : %s\n"EOC, tbl[i]);
			ft_dy_tab_suppr_index(context->env, i);
		}
		else
			i++;
	}
	return ;
}

/*
** sh_env_save_get_index:
**	identical to sh_vars_get_index, but it can use and find keys that
**	are not finished by '=' char.
**
**	Returned Value :
**		-1 : key not foud
**		Else : index of the key in saved_env
*/

int			sh_env_save_get_index(t_dy_tab *saved_env, char *key)
{
	int		i;
	int		j;
	char	**tbl;

	i = 0;
	tbl = (char**)saved_env->tbl;
	while (tbl[i])
	{
		j = 0;
		while (tbl[i][j] && key[j] && tbl[i][j] == key[j])
			j++;
		if (key[j] == 0 && (tbl[i][j] == '=' || tbl[i][j] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
