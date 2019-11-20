/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:48:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 03:01:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_env_save_restore_command_run:
**	Body of sh_env_save_restore_command, see it description.
**	First case in used with the export builtin, the second in other cases.
*/

static int	sh_env_save_restore_command_run(
	t_context *context, int *i, char **tbl, char *equal)
{
	int		index;

	*equal = '\0';
	if ((index = sh_vars_get_index(context->env, tbl[*i])) == -1)
	{
		*equal = '=';
		if (ft_dy_tab_add_str(context->env, tbl[*i]))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (0)"));
		return (SUCCESS);
	}
	else
	{
		*equal = '=';
		if (!ft_strequ(tbl[*i], ((char**)context->env->tbl)[index]))
		{
			free(context->env->tbl[index]);
			if (!(context->env->tbl[index] = ft_strdup(tbl[*i])))
				return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (1)"));
		}
	}
	(*i)++;
	return (SUCCESS);
}

/*
** sh_env_save_restore_command:
**	Function used to restore env between two commands if there were at least
**	one parameter in context->params.
**	The aim is to synchronize env with the content of saved_env.
**	For every assignment in saved_env if entry is not in env, it's added,
**	if entry exist but value is not the same it is updated in env.
**	Finally sh_env_save_restore_command_clean delete any entry in env
**	that is not in saved_env and any non assigned key in env.
**
**	Returned Values:
**		FAILURE : Malloc ERROR
**		SUCCESS : sync is successfull
*/

static int	sh_env_save_restore_command(t_context *context)
{
	int		i;
	char	**tbl;
	char	*equal;
	int		ret;

	i = 0;
	tbl = (char**)context->saved_env->tbl;
	while (tbl[i])
	{
		if (!(equal = ft_strchr(tbl[i], '=')))
		{
			i++;
			continue ;
		}
		ret = sh_env_save_restore_command_run(context, &i, tbl, equal);
		if (ret != SUCCESS)
			return (ret);
	}
	sh_env_save_restore_command_clean(context);
	return (SUCCESS);
}

/*
** sh_env_save_restore_no_command_run:
**	Body of sh_env_save_restore_no_command, see it description.
*/

static int	sh_env_save_restore_no_command_run(
	t_context *context, char **tbl, int *i, char *equal)
{
	int		index;

	*equal = '\0';
	if ((index = sh_env_save_get_index(context->saved_env, tbl[*i])) == -1)
	{
		*equal = '=';
		if ((sh_vars_assignment(NULL, context->vars, tbl[*i])))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (2)"));
		ft_dy_tab_suppr_index(context->env, *i);
		return (SUCCESS);
	}
	*equal = '=';
	if (!ft_strequ(tbl[*i], ((char**)context->saved_env->tbl)[index]))
	{
		free(context->saved_env->tbl[index]);
		if (!(context->saved_env->tbl[index] = ft_strdup(tbl[*i])))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (3)"));
	}
	(*i)++;
	return (SUCCESS);
}

/*
** sh_env_save_restore_no_command:
**	Function used to restore env between two commands if there were only
**	assignment words in command.
**	Any var assigned by an assignment word in temporary stored in env.
**
**	Returned Values:
**		SUCCESS
**		FAILURE : malloc error
*/

static int	sh_env_save_restore_no_command(t_context *context)
{
	int		i;
	char	**tbl;
	char	*equal;
	int		ret;

	i = 0;
	tbl = (char**)context->env->tbl;
	while (tbl[i])
	{
		if (!(equal = ft_strchr(tbl[i], '=')))
			return (FAILURE);
		ret = sh_env_save_restore_no_command_run(context, tbl, &i, equal);
		if (ret)
			return (ret);
	}
	return (SUCCESS);
}

/*
**	sh_env_save_restore :
**	Function called to clear the env after a simple command had been called,
**	(executed or not).
**
**	Returned Values:
**		SUCCESS
**		FAILURE : malloc error
*/

int			sh_env_save_restore(t_context *context)
{
	if (context->params && context->params->tbl
			&& ((char**)context->params->tbl)[0])
		return (sh_env_save_restore_command(context));
	else
		return (sh_env_save_restore_no_command(context));
}
