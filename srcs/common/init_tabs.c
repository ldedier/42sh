/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:37:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/28 17:28:50 by jdugoudr         ###   ########.fr       */
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

int			sh_update_shell_lvl(t_shell *shell)
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
	int			len;
	int			i;
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
			return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_env"));
		}
		i++;
	}
	shell->env = tbl;
	if (sh_main_init_env_special_vars(shell) == FAILURE)
	{
		ft_dy_tab_del_ptr(shell->env);
		shell->env = NULL;
		ft_dy_tab_del_ptr(shell->saved_env);
		shell->saved_env = NULL;
		return (FAILURE);
	}
	if (!(shell->saved_env = ft_dy_tab_cpy_str(shell->env)))
	{
		ft_dy_tab_del_ptr(tbl);
		return (sh_perror(SH_ERR1_MALLOC, "sh_main_init_env"));
	}
	return (SUCCESS);
}

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
	if (BONUS_DOLLAR_VARIABLE)//can we not just expande $? with shell->ret_value ?? instead of having a specific env var ?
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
