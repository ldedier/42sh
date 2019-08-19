/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vars_tools_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 22:21:50 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/19 12:44:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vars_mod_key:
**	modify the the value of an assignment in a t_dy_tab
**	If value does not exists it calls sh_vars_add_key
**	return:
**		SUCESS or FAILURE
*/

int		sh_vars_mod_key(t_dy_tab *vars, char *key, char *value)
{
	int		index;
	char	*buff;

	if ((index = sh_vars_get_index(vars, key)) == -1)
		return (sh_vars_add_key(vars, key, value));
	if (!(buff = ft_strjoin_3(key, "=", value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_vars_mod_key"));
	if (vars)
	{
		free(vars->tbl[index]);
		vars->tbl[index] = buff;
	}
	return (SUCCESS);
}

/*
** sh_vars_add_key:
**	add an assignment in a t_dy_tab, using key, value arguments
**	If value already exists it calls sh_vars_mod_key
**	return:
**		SUCESS or FAILURE
*/

int		sh_vars_add_key(t_dy_tab *vars, char *key, char *value)
{
	char	*buff;

	if (sh_vars_get_index(vars, key) != -1)
		return (sh_vars_mod_key(vars, key, value));
	if (!(buff = ft_strjoin_3(key, "=", value)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_vars_add_key (1)"));
	if (ft_dy_tab_add_ptr(vars, buff))
	{
		free(buff);
		return (sh_perror(SH_ERR1_MALLOC, "sh_vars_add_key (2)"));
	}
	return (SUCCESS);
}

/*
** sh_vars_assignment:
**	Treat any assignment with form "key=value" and call sh_vars_add_value
**	or sh_vars_mod_value, with well formatted arguments
**	It first look for the key in env, then in vars, if the key already exists
**	value is modified, else the key is created in the vars
**	(or in env if var is NULL).
**	return:
**		SUCESS
**		FAILURE : Malloc error
**		ERROR : no '=' char found in assignment
*/

int		sh_vars_assignment(t_dy_tab *env, t_dy_tab *vars, char *assignment)
{
	char	*buf;
	char	*value;
	int		res;

	if (!(buf = ft_strchr(assignment, '=')))
		return (ERROR);
	*buf = 0;
	value = buf + 1;
	if (env && sh_vars_get_index(env, assignment) != -1)
		res = sh_vars_mod_key(env, assignment, value);
	else if (vars && sh_vars_get_index(vars, assignment) != -1)
		res = sh_vars_mod_key(vars, assignment, value);
	else if (vars)
		res = sh_vars_add_key(vars, assignment, value);
	else
		res = sh_vars_add_key(env, assignment, value);
	*buf = '=';
	return (res);
}

/*
** sh_vars_assign_key_val:
**	Treat any assignment as sh_vars_assignment, but it takes assignation
**	as two strings : key and value
**	Return Values:
**		FAILURE : malloc error
**		SUCCESS
*/

int		sh_vars_assign_key_val(
	t_dy_tab *env, t_dy_tab *vars, char *key, char *value)
{
	int		res;

	if (env && sh_vars_key_exist(env, key))
		res = sh_vars_mod_key(env, key, value);
	else if (vars && sh_vars_key_exist(vars, key))
		res = sh_vars_mod_key(vars, key, value);
	else if (vars)
		res = sh_vars_add_key(vars, key, value);
	else
		res = sh_vars_add_key(env, key, value);
	return (res);
}

void	sh_vars_del_key(t_dy_tab *vars, char *key)
{
	int		index;

	index = sh_vars_get_index(vars, key);
	if (index == -1)
		return ;
	ft_dy_tab_suppr_index(vars, index);
	return ;
}
