/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_simple_command.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/22 13:14:17 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_found_sc_search_in_hash(t_context *context, t_binary *binary,
			t_hash_finder finder)
{
	binary->hits++;
	if (access(binary->path, F_OK))
	{
		if (finder.prev)
			finder.prev->next = finder.prev->next->next;
		else
			*finder.list = (*(finder.list))->next;
		sh_free_binary(binary);
		free(finder.current);
		return (ERROR);
	}
	if (sh_traverse_sc_check_perm(context,
				binary->path, binary->name) == ERROR)
		return (SUCCESS);
	if (!(context->path = ft_strdup(binary->path)))
		return (FAILURE);
	return (SUCCESS);
}

long		sh_traverse_sc_search_in_hash(t_context *context)
{
	t_binary		*binary;
	t_hash_finder	finder;

	finder = ft_hash_table_find(context->shell->binaries,
		context->params->tbl[0], ft_hash_str, compare_str_to_binary);
	if (finder.found)
	{
		binary = (t_binary *)finder.content;
		return (sh_found_sc_search_in_hash(context, binary, finder));
	}
	return (ERROR);
}

static long	sh_traverse_sc_search_in_dir_found(char *path, DIR *dir,
			t_dirent *dirent, t_context *context)
{
	char *buf;

	if (!(buf = ft_strjoin_path(path, dirent->d_name)))
	{
		closedir(dir);
		return (sh_perror(SH_ERR1_MALLOC,
					"traverse_sc_search_in_dir"));
	}
	if (sh_traverse_sc_check_perm_quiet(buf) == ERROR)
	{
		free(buf);
		return (KEEP_READ);
	}
	context->path = buf;
	closedir(dir);
	if (sh_update_hash_table(context->shell,
				context->path, context->params->tbl[0]) != SUCCESS)
		return (FAILURE);
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

static long	sh_traverse_sc_search_in_dir(
	char *path, t_context *context)
{
	t_dirent	*dirent;
	int			ret;
	DIR			*dir;

	if (!*path)
		dir = opendir(".");
	else
		dir = opendir(path);
	if (!dir)
		return (SUCCESS);
	while ((dirent = readdir(dir)))
	{
		if (ft_strequ(dirent->d_name, context->params->tbl[0]))
		{
			if ((ret = sh_traverse_sc_search_in_dir_found(path, dir,
				dirent, context)) != KEEP_READ)
				return (ret);
			else
				continue ;
		}
	}
	closedir(dir);
	return (SUCCESS);
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

long		sh_traverse_sc_search_in_path(t_context *context)
{
	char	*buffer;
	char	*path;

	if (!(buffer = sh_vars_get_value(context->env, context->vars, "PATH")))
		return (sh_traverse_sc_search_in_dir(".", context));
	while ((path = ft_strsep(&buffer, ":")))
	{
		if (sh_traverse_sc_search_in_dir(path, context) == FAILURE)
		{
			ft_strsep(NULL, NULL);
			return (FAILURE);
		}
		if (context->path)
			break ;
	}
	ft_strsep(NULL, NULL);
	return (SUCCESS);
}
