/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/17 21:44:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define TYPE_USAGE			"type [-atp] name [name ...]"
#define TYPE_A_OPT			0
#define TYPE_A_OPT_USAGE	"Print all the places that contain an executable named name"
#define TYPE_P_OPT			1
#define TYPE_P_OPT_USAGE	"Print the path of the disk file that name would execute."
#define TYPE_T_OPT			2
#define TYPE_T_OPT_USAGE	"Print a string describing the file type"

static int	sh_builtin_type_search_in_dir_found(char *path, DIR *dir,
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
	context->path = buf;
	closedir(dir);
	return (SUCCESS);
}

/*
** sh_traverse_sc_search_in_dir:
**		Look for any executable matching the context->params->tbl[0],
**		in the directory defined by path and dir
**		If any valid match is ffound, context->path is filled
**
**		return :
**		FAILURE : malloc error
**		SUCCESS : any error occur
*/

int			sh_builtin_type_search_in_dir(
	char *path, DIR *dir, t_context *context, char *name)
{
	t_dirent	*dirent;
	int			ret;

	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, name))
		{
			if ((ret = sh_builtin_type_search_in_dir_found(path, dir,
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
** sh_traverse_sc_search_in_path:
**	Use the PATH env variable to look for any executable named like
**	context->params->tbl[0], with correct execution rights.
**	If it found a valid match, context->path is filled with path of executable
**	return :
**		FAILURE : malloc error
**		ERROR : $PATH is empty
**		SUCCESS : Any error occured
*/

int			sh_builtin_type_search_in_path(t_context *context, char *name, t_args args[])
{
	char	**split;
	int		i;
	DIR		*dir;
	char	*buffer;
	int		ret;
	int		found;

	if (!(buffer = sh_vars_get_value(context->env, context->vars, "PATH")))
		return (ERROR);
	if (!(split = ft_strsplit(buffer, ':')))
		return (FAILURE);
	i = 0;
	found = 0;
	while (split[i])
	{
		if (context->path)
			ft_strdel(&(context->path));
		if (!(dir = opendir(split[i])))
		{
			i++;
			continue ;
		}
		ret = sh_builtin_type_search_in_dir(split[i], dir, context, name);
		i++;
		if (ret == FAILURE)
			return (FAILURE);
		if (ret == SUCCESS && context->path)
		{
			found++;
			if (args[TYPE_P_OPT].value && args[TYPE_P_OPT].priority > args[TYPE_T_OPT].priority)
				ft_dprintf(context->fd[FD_OUT], "%s\n", context->path);
			else if (args[TYPE_T_OPT].value)
				ft_dprintf(context->fd[FD_OUT], "file\n");
			else
				ft_dprintf(context->fd[FD_OUT], "%s is %s\n", name, context->path);
			if (args[TYPE_A_OPT].value)
				continue ;
			else
				break ;
		}
	}
	ft_strtab_free(split);
	if (found)
		return (SUCCESS);
	return (ERROR);
}
