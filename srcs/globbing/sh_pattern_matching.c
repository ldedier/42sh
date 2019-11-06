/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 07:35:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/06 22:35:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_is_pattern_matching(char *name, t_list *regexp_head)
{
	t_regexp	*regexp;
	int			i;
	int			ret;

	if (!regexp_head)
		return (SUCCESS); // is it used ?
	i = 0;
	ret = SUCCESS;
	regexp = (t_regexp*)regexp_head->content;
	if (regexp->type == REG_FINAL_SLASH)
		regexp_head = regexp_head->next;
	if (*name == '.' && (regexp->type != REG_STR || regexp->value[0] != '.'))
		return (ERROR);
	while (regexp_head && name[i])
	{
		regexp = (t_regexp*)regexp_head->content;
		if (regexp->type == REG_STR)
			ret = sh_pattern_matching_str(name, regexp, &i);
		else if (regexp->type == REG_QUEST)
			ret = sh_pattern_matching_quest(name, regexp, &i);
		else if (regexp->type == REG_BRACE)
			ret = sh_pattern_matching_brace(name, regexp, &i);
		else if (regexp->type == REG_STAR)
			ret = sh_pattern_matching_star(name, regexp, &i, regexp_head);
		if (ret)
			return (ret);
		if (sh_verbose_globbing())
			{ft_dprintf(2, BLUE"\t%s : matched : (", name); t_regexp_show(regexp);ft_dprintf(2, ")\n"EOC);}
		regexp_head = regexp_head->next;
	}
	while (regexp_head && ((t_regexp*)regexp_head->content)->type == REG_STAR)
		regexp_head = regexp_head->next;
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}

/*
** check_for_final_slash:
**	If final slash had been specified, only directories and symlinks pointing
**	a directorie shall be kept.
**
**	Returned Values:
**		SUCCESS : File can be valid
**		ERROR : File cannot be valid
*/

static int	check_for_final_slash(t_list *regexp_list, char *path)
{
	t_regexp	*regexp;
	struct stat	st;
	
	regexp = (t_regexp*)regexp_list->content;
	if (regexp->type != REG_FINAL_SLASH)
		return (SUCCESS);
	if (lstat(path, &st) == -1)
		return (ERROR);
	if (!S_ISDIR(st.st_mode))
	{
		if (sh_verbose_globbing())
			ft_dprintf(2, RED"\t%s is not a directory\n"EOC, path);
		return(ERROR);
	}
	return (SUCCESS);
}

static void	pattern_matching_push_find_place(t_list **head, t_list **prev, char *filename)
{
	while (*head)
	{
		if (ft_strcmp((char*)(*head)->content, filename) > 0)
			return ;
		(*prev) = *head;
		(*head) = (*head)->next;
	}
	return ;
}

static int	pattern_matching_push(t_list **matches, t_list *new)
{
	t_list	*head;
	t_list	*prev;

	if (!*matches)
	{
		*matches = new;
		return (SUCCESS);
	}
	head = *matches;
	prev = NULL;
	pattern_matching_push_find_place(&head, &prev, (char*)new->content);
	if (prev == NULL)
	{
		new->next = head;
		*matches = new;
	}
	else if (head == NULL)
		prev->next = new;
	else
	{
		prev->next = new;
		new->next = head;
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

static int	pattern_matching_read_directory(char *path, t_list **regexp_list, t_list **matchs, t_dirent *dirent)
{
	char	*new_path;

	if (sh_is_pattern_matching(dirent->d_name, *regexp_list) == SUCCESS)
	{
		new_path = ft_strjoin_path(path, dirent->d_name); //protect && leaks
		if (new_path && ((t_regexp*)(*regexp_list)->content)->type == REG_FINAL_SLASH)
			new_path = ft_strjoin_free(new_path, "/", 1);
		if (!new_path)
			return (sh_perror(SH_ERR1_MALLOC, "pattern_matching")); // leaks ??
		if (check_for_final_slash(*regexp_list, new_path))
			return (SUCCESS);
		if (regexp_list[1])
		{
			if (sh_verbose_globbing())
				ft_dprintf(2, "recursive call : %s\n", new_path);
			sh_expansions_pattern_matching(new_path, regexp_list + 1, matchs);
		}
		else
		{
			if (sh_verbose_globbing())
				ft_dprintf(2, GREEN"\t\tfound valid path : %s\n"EOC, new_path);
			pattern_matching_push(matchs, ft_lstnew(new_path, ft_strlen(new_path) + 1)); // protect lst_new malloc
		}
	}
	else  if (sh_verbose_globbing())
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
		return (SUCCESS); // perrror ? permissions
	while ((dirent = readdir(dir)))
	{
		if (sh_verbose_globbing())
			ft_dprintf(2, "working on path : %s/%s\n", path, dirent->d_name);
		ret = pattern_matching_read_directory(path, regexp_list, matchs, dirent);
		if (ret)
			return (ret);
	}
	return (SUCCESS);
}
