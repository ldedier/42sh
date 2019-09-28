/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:48:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/28 03:41:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_env_diff(t_context *context)
{
	int		i;
	char	**env;
	char	**save;

	if (!context->env || !context->saved_env)
	{
		ft_dprintf(2, "diff : one table is NULL\n");
		return ;
	}
	env = (char**)context->env->tbl;
	save = (char**)context->saved_env->tbl;
	i = 0;
	while (env[i] || save[i])
	{
		if (env[i] && save[i])
		{
			if (!ft_strequ(env[i], save[i]))
				ft_dprintf(2, "env  : %s\nsave : %s\n", env[i], save[i]);
		}
		else
		{
			if (env[i])
				ft_dprintf(2, "env  : %s\n", env[i]);
			if (save[i])
				ft_dprintf(2, "save : %s\n", save[i]);
		}
		i++;
	}
}

static int	sh_env_save_dup(t_context *context)
{
	t_dy_tab	*save;
	int			i;
	int			len;
	char		**env;

	len = context->env->current_size;
	if (!(save = ft_dy_tab_new(len)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_env_save_dup (1)"));
	i = 0;
	env = (char**)context->env->tbl;
	while (i < len)
	{
		if (ft_dy_tab_add_str(save, env[i]))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save_dup (2)"));
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

int			sh_env_save_restore(t_context *context, int command)
{
	int		i;
	char	**tbl;
	char	*equal;
	char	save;
	int		index_saved;

	i = 0;
	tbl = (char**)context->env->tbl;
	ft_dprintf(2, "diff : starting restore (command : %d)\n", command);
	sh_env_diff(context);
	while (tbl[i])
	{
		if (!(equal = ft_strchr(tbl[i], '=')))
			return (ERROR); // :/
		save = *equal;
		*equal = '\0';
		// Si dans env et pas dans save env 
		if ((index_saved = sh_vars_get_index(context->saved_env, tbl[i])) == -1)
		{
			if (!command)
			{
				*equal = save;
				ft_dy_tab_add_str(context->vars, tbl[i]); // protect
			}
			// common to command and !command
			ft_dy_tab_suppr_index(context->env, i);
			continue ;
		}
		// Si dans env et aussi dans saved env
		else
		{
			*equal = save;
			sh_vars_get_index(context->saved_env, tbl[i]);
		
			if (!ft_strequ(tbl[i], ((char**)context->saved_env->tbl)[index_saved]))
			{
				// Si command : copy saved_env value here
				if (command)
				{
					free(tbl[i]);
					tbl[i] = ft_strdup(((char**)context->saved_env->tbl)[index_saved]); // protect
				}
				// Si !command : copy env_value to saved_env
				else
				{
					free(((char**)context->saved_env->tbl)[index_saved]);
					((char**)context->saved_env->tbl)[index_saved] = ft_strdup(tbl[i]);
				}
			}
		}
		i++;
	}
	i = 0;
	tbl = (char**)context->saved_env->tbl;
	while (tbl[i])
	{
		if (!ft_strchr(tbl[i], '='))
			ft_dy_tab_add_str(context->env, tbl[i]); // protect
		i++;
	}
	ft_dprintf(2, "diff : finished restore\n");
	sh_env_diff(context);
	return (SUCCESS);

	// if (!context->saved_env)
	// 	return (SUCCESS);
	// ft_dy_tab_del(context->env);
	// context->env = context->saved_env;
	// context->shell->env = context->saved_env;
	// context->saved_env = NULL;
	// // if (sh_env_save_dup(context))
	// // 	return (FAILURE);
	// return (SUCCESS);
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
