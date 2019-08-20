/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:48:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/20 18:47:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_env_save_dup(t_context *context)
{
	t_dy_tab	*save;
	int			i;
	int			len;
	char		**env;

	len = context->env->current_size;
	if (!(save = ft_dy_tab_new(len)))
		return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_env_save_dup (1)"));
	i = 0;
	env = (char**)context->env->tbl;
	while (i < len)
	{
		if (ft_dy_tab_add_str(save, env[i]))
			return (sh_perror_fd(context->fd[FD_ERR], SH_ERR1_MALLOC, "sh_env_save_dup (2)"));
		i++;
	}
	context->saved_env = save;
	return (SUCCESS);
}

int			sh_env_save(t_context *context)
{
	if (context->saved_env)
		ft_dy_tab_del(context->saved_env);
	return (sh_env_save_dup(context));
}

int			sh_env_save_restore(t_context *context)
{
	ft_dy_tab_del(context->env);
	context->env = context->saved_env;
	context->shell->env = context->saved_env;
	context->
	context->saved_env = NULL;
	return (SUCCESS);
}

void		sh_env_save_delete_exported(t_context *context)
{
	int			i;
	int			len;
	char		**env;

	i = 0;
	len = context->env->current_size;
	env = (char**)context->env->tbl;
	while (i < len)
	{
		if (!ft_strchr(env[i], '='))
			ft_dy_tab_suppr_index(context->env, i);
		i++;
	}
	return ;
}
