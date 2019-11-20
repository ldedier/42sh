/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 07:35:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:00:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** check_for_final_slash:
**	If final slash had been specified, only directories and symlinks pointing
**	a directorie shall be kept.
**	If an error occured path string wil be freed.
**
**	Returned Values:
**		SUCCESS : File can match
**		ERROR : File do not match
*/

static int	check_for_final_slash(t_list *regexp_list, char *path)
{
	t_regexp	*regexp;
	struct stat	st;

	regexp = (t_regexp*)regexp_list->content;
	if (regexp->type != REG_FINAL_SLASH)
		return (SUCCESS);
	if (lstat(path, &st) == -1)
	{
		free(path);
		return (ERROR);
	}
	if (!S_ISDIR(st.st_mode))
	{
		if (sh_verbose_globbing())
			ft_dprintf(2, RED"\t%s is not a directory\n"EOC, path);
		free(path);
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** pattern_matching_read_directory:
**	If current filename match pattern, then it create the new path, by
**	concatenating path, and new file, adding a '/'. Then it recursively
**	call it's father function, or if there are no more patterns it add a
**	new match in list.
**	Else, filename is invalid and current path is dropped.
*/

static int	pattern_matching_read_directory(
	char *path, t_list **regexp_list, t_list **matchs, t_dirent *dirent)
{
	char	*new_path;

	if (sh_is_pattern_matching(dirent->d_name, *regexp_list) == SUCCESS)
	{
		new_path = ft_strjoin_path(path, dirent->d_name);
		if (new_path &&
			((t_regexp*)(*regexp_list)->content)->type == REG_FINAL_SLASH)
			new_path = ft_strjoin_free(new_path, "/", 1);
		if (!new_path)
			return (sh_perror(SH_ERR1_MALLOC, "pattern_matching"));
		if (check_for_final_slash(*regexp_list, new_path))
			return (SUCCESS);
		if (regexp_list[1])
			sh_expansions_pattern_matching(new_path, regexp_list + 1, matchs);
		else
		{
			if (sh_verbose_globbing())
				ft_dprintf(2, GREEN"\t\tfound valid path : %s\n"EOC, new_path);
			return (pattern_matching_push_new(matchs, new_path));
		}
	}
	else if (sh_verbose_globbing())
		ft_dprintf(2, RED"\t\tfound invalid path : %s\n"EOC, dirent->d_name);
	return (SUCCESS);
}

/*
**	sh_expansions_pattern_matching:
**	Recursive function used to check if files contained in the directory
**	designated by path can match regexp epression described in regexp_list[0].
**	Check in every coumponent of path, matching patterns stored in regexp_list.
**	If regexp_list is finished (regexp_list[1] == NULL), a match is added to
**	matches list.
**	Else, if any pattern cannot be feated, it return a SUCCESS, but match are
**	not created.
**
**	Returned Values:
**		SUCCESS : No malloc errors (even if no matches are found)
**		FAILURE : Malloc error
*/

int			sh_expansions_pattern_matching(
	char *path, t_list **regexp_list, t_list **matchs)
{
	DIR			*dir;
	t_dirent	*dirent;
	int			ret;

	if (!*path)
		dir = opendir("./");
	else
		dir = opendir(path);
	if (!dir)
	{
		free(path);
		return (SUCCESS);
	}
	ret = SUCCESS;
	while ((dirent = readdir(dir)) && !ret)
	{
		if (sh_verbose_globbing())
			ft_dprintf(2, "working on path : %s/%s\n", path, dirent->d_name);
		ret = pattern_matching_read_directory(
			path, regexp_list, matchs, dirent);
	}
	free(path);
	closedir(dir);
	return (ret);
}
