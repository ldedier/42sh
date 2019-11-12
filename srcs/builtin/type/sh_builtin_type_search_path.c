/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type_search_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/12 08:15:38 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	search_in_dir_check_perm(char *path, DIR *dir,
			t_dirent *dirent, t_context *context)
{
	char *buf;

	if (!(buf = ft_strjoin_path(path, dirent->d_name)))
	{
		closedir(dir);
		return (sh_perror(SH_ERR1_MALLOC,
					"builtin_type_search_path"));
	}
	if (sh_traverse_sc_check_perm_quiet(buf) == ERROR)
	{
		free(buf);
		return (KEEP_READ);
	}
	if (context->path)
		ft_strdel(&context->path);
	context->path = buf;
	closedir(dir);
	return (SUCCESS);
}

int			sh_builtin_type_search_in_dir(
	char *path, DIR *dir, t_context *context, char *name)
{
	t_dirent	*dirent;
	int			ret;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, name))
		{
			if ((ret = search_in_dir_check_perm(path, dir,
				dirent, context)) != KEEP_READ)
				return (ret);
			else
				return (SUCCESS);
		}
	}
	closedir(dir);
	return (ERROR);
}

/*
** show_success_message:
**	ERROR means : continue reading in dir, because -a flag is on.
**
**	Returned Values
**		SUCCESS : 
**		ERROR : 
**		FAILURE : 
*/

static int	show_success_message(
	t_context *context, t_args *args, char *name, int *found)
{
	(*found) += 1;
	if (args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
		ft_dprintf(FD_OUT, "%s\n", context->path);
	else if (args[TYPE_T_OPT].value)
		ft_dprintf(FD_OUT, "file\n");
	else
		ft_dprintf(FD_OUT, "%s is %s\n", name, context->path);
	if (args[TYPE_A_OPT].value)
		return (ERROR);
	else
		return (SUCCESS);
}

int			sh_builtin_type_search_in_path(
	t_context *context, char *name, t_args args[])
{
	char		*env_path;
	char		*path;
	DIR			*dir;
	int			found;
	int			ret;

	found = 0;
	ft_strsep(NULL, 0);
	if (!(env_path = sh_vars_get_value(context->env, context->vars, "PATH")))
		return (ERROR);
	path = NULL;
	ret = ERROR;
	while ((path = ft_strsep(&env_path, ':')))
	{
		if (ret != ERROR)
			continue ;
		if (!(dir = opendir(path)))
			continue ;
		ret = sh_builtin_type_search_in_dir(path, dir, context, name);
		if (ret == SUCCESS && context->path)
			ret = show_success_message(context, args, name, &found);
	}
	if (ret == FAILURE)
		return (FAILURE);
	if (found)
		return (SUCCESS);
	return (ERROR);
}
