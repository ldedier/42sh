/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:48:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/28 23:12:18 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_env_save_restore_command_clean:
**	Delete assignment in env table that are not insaved_env table.
*/

static void	sh_env_save_restore_command_clean(t_context *context)
{
	int		i;
	char	**tbl;
	char	*equal;
	char	save;

	tbl = (char**)context->env->tbl;
	i = 0;
	while (tbl[i])
	{
		if ((equal = ft_strchr(tbl[i], '=')))
		{
			save = *equal;
			*equal = '\0';
			if (sh_vars_get_index(context->saved_env, tbl[i]) == -1)
				ft_dy_tab_suppr_index(context->env, i);
			else
			{
				i++;
				*equal = save;
			}
		}
		else
		{
			ft_dy_tab_suppr_index(context->env, i);
			ft_dprintf(2, "restoring env : deleted : %s\n", tbl[i]);
		}
	}
}

static int	sh_env_save_restore_command_run(
	t_context *context, int *i, char **tbl, char *equal)
{
	char	save;
	int		index;

	save = *equal;
	*equal = '\0';
	if ((index = sh_vars_get_index(context->env, tbl[*i])) == -1)
	{
		*equal = save;
		if (ft_dy_tab_add_str(context->env, tbl[*i]))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (0)"));
		return (SUCCESS);
	}
	else
	{
		*equal = save;
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

static int	sh_env_save_restore_no_command_run(
	t_context *context, char **tbl, int *i, char *equal)
{
	char	save;
	int		index;

	save = *equal;
	*equal = '\0';
	if ((index = sh_vars_get_index(context->saved_env, tbl[*i])) == -1)
	{
		*equal = save;
		if ((sh_vars_assignment(NULL, context->vars, tbl[*i])))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (2)"));
		ft_dy_tab_suppr_index(context->env, *i);
		return (SUCCESS);
	}
	*equal = save;
	if (!ft_strequ(tbl[*i], ((char**)context->saved_env->tbl)[index]))
	{
		free(context->saved_env->tbl[index]);
		if (!(context->saved_env->tbl[index] = ft_strdup(tbl[*i])))
			return (sh_perror(SH_ERR1_MALLOC, "sh_env_save (3)"));
	}
	(*i)++;
	return (SUCCESS);
}

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
			return (ERROR);
		ret = sh_env_save_restore_no_command_run(context, tbl, &i, equal);
		if (ret)
			return (ret);
	}
	return (SUCCESS);
}

int			sh_env_save_restore(t_context *context)
{
	if (context->params && context->params->tbl
			&& ((char**)context->params->tbl)[0])
		return (sh_env_save_restore_command(context));
	else
		return (sh_env_save_restore_no_command(context));
}
