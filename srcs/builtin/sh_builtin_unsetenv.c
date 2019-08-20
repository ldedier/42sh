/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 18:37:17 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/10 11:29:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_unsetenv_usage(int fderr)
{
	ft_dprintf(fderr, "usage : unsetenv varname [...]\n");
	return (ERROR);
}

int			sh_builtin_unsetenv(t_context *context)
{
	int i;
	int	j;

	i = 1;
	while (context->params->tbl[i])
	{
		if (sh_vars_key_exist(context->env, context->params->tbl[i]))
		{
			if (!ft_strcmp(context->params->tbl[i], "PATH"))
				sh_builtin_hash_empty_table(context->shell);
			j = sh_vars_get_index(context->env, context->params->tbl[i]);
			if (j != -1)
				ft_dy_tab_suppr_index(context->env, j);
		}
		i++;
	}
	if (i == 1)
		return (sh_builtin_unsetenv_usage(context->fd[FD_ERR]));
	return (SUCCESS);
}
