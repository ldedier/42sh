/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:47:26 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 19:59:44 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char	*sh_update_shell_lvl_get_value(t_shell *shell)
{
	char	*str;
	int		new_lvl;
	char	*new_lvl_str;

	if (!(str = sh_vars_get_value(shell->env, NULL, "SHLVL")))
		new_lvl = 1;
	else
	{
		new_lvl = ft_atoi(str) + 1;
		if (new_lvl > 1000)
		{
			sh_perror("warning", "shell level too high, reseting to 1");
			new_lvl = 1;
		}
	}
	if (!(new_lvl_str = ft_itoa(new_lvl)))
	{
		ft_dy_tab_del_ptr(shell->env);
		return (sh_perrorn(SH_ERR1_MALLOC, "sh_update_shell_lvl"));
	}
	return (new_lvl_str);
}

static int	sh_update_shell_lvl(t_shell *shell)
{
	char	*new_lvl_str;

	if (!(new_lvl_str = sh_update_shell_lvl_get_value(shell)))
		return (FAILURE);
	if (sh_vars_assign_key_val(shell->env, NULL, "SHLVL", new_lvl_str))
	{
		free(new_lvl_str);
		ft_dy_tab_del_ptr(shell->env);
		return (sh_perror(SH_ERR1_MALLOC, "sh_update_shell_lvl"));
	}
	free(new_lvl_str);
	return (SUCCESS);
}

/*
** sh_main_init_env_special_vars:
**	Create some special vars in environment :
**		SHLVL is initalized
**		If pwd is not set, it is filled using getcwd
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS
*/

static int	sh_main_init_env_special_vars(t_shell *shell)
{
	char	*pwd;

	if (sh_update_shell_lvl(shell) != SUCCESS)
		return (FAILURE);
	if (sh_vars_get_index(shell->env, "PWD") == -1)
	{
		if (!(pwd = sh_builtin_pwd_physical()))
			return (FAILURE);
		if (sh_vars_assign_key_val(shell->env, NULL, "PWD", pwd) == FAILURE)
		{
			free(pwd);
			return (FAILURE);
		}
		free(pwd);
	}
	return (SUCCESS);
}

static int	init_env_dup_original_env(t_shell *shell, char **env)
{
	int			i;
	int			len;
	t_dy_tab	*tbl;

	len = ft_strtab_len(env);
	if (!(tbl = ft_dy_tab_new(len + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_env"));
	i = 0;
	while (i < len)
	{
		if (ft_dy_tab_add_str(tbl, env[i]))
		{
			ft_dy_tab_del_ptr(tbl);
			return (sh_perror(SH_ERR1_MALLOC, "init_env_dup_original_env"));
		}
		i++;
	}
	shell->env = tbl;
	return (SUCCESS);
}

/*
** sh_main_init_env:
**	Create a t_dy_tab cloning the char **env. Then it calls the function
**	sh_main_init_env_special_vars to modify this nnew env.
**	If any error occur, every locally allocated memory is free.
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS
*/

int			sh_main_init_env(t_shell *shell, char **env)
{
	if (init_env_dup_original_env(shell, env))
		return (FAILURE);
	if (sh_main_init_env_special_vars(shell) == FAILURE)
	{
		ft_dy_tab_del_ptr(shell->env);
		shell->env = NULL;
		return (FAILURE);
	}
	if (!(shell->saved_env = ft_dy_tab_cpy_str(shell->env)))
	{
		ft_dy_tab_del_ptr(shell->env);
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_env"));
	}
	return (SUCCESS);
}
