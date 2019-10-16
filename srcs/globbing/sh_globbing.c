/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/16 07:41:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	pattern_matching(char *path, t_list **regexp_list, t_dy_tab *quotes, t_list **matchs)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		*new_path;

	if (!*path)
		dir = opendir("./");
	else
		dir = opendir(path);
	if (!dir)
		return (ERROR);
	while ((dirent = readdir(dir)))
	{
		if (sh_is_pattern_matching(dirent->d_name, *regexp_list) == SUCCESS)
		{
			new_path = ft_strjoin_path(path, dirent->d_name); //protect && leaks
			if (regexp_list[1])
			{
				if (sh_verbose_globbing())
					ft_dprintf(2, "recursive call : %s\n", new_path);
				pattern_matching(new_path, regexp_list + 1, quotes, matchs);
			}
			else
			{
				if (sh_verbose_globbing())
					ft_dprintf(2, GREEN"found valid path : %s\n"EOC, new_path);
				ft_lstadd_last(matchs, ft_lstnew(new_path, ft_strlen(new_path) + 1)); // protect lst_new malloc
			}
		}
	}
	return (SUCCESS);
}

static int	init_path(char **path, char *str)
{
	if (*str == '/')
		*path = ft_strdup("/");
	else if (str[0] == '.' && str[1] == '/')
		*path = ft_strdup("./");
	else
		*path = ft_strdup("");
	if (!path)
		return (FAILURE); //perror
	return (SUCCESS);
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
*/

int			sh_expansions_globbing(t_context *context, t_ast_node *father, t_dy_tab *quotes)
{
	t_list		*head;
	t_ast_node	*child;
	char		*str;
	t_list		*matches;
	t_dy_tab	*regexp_tab;
	char		*path;

	head = father->children;
	regexp_tab = NULL;
	matches = NULL;
	while (head)
	{
		child = (t_ast_node*)head->content;
		str = child->token->value;
		sh_regexp_parse(str, &regexp_tab);
		if (regexp_tab) //modify
		{
			init_path(&path, str);
			pattern_matching(path, (t_list**)regexp_tab->tbl, quotes, &matches);
			if (matches)
			{
				if (sh_verbose_globbing())
					{ft_lstput_fd(matches, 2); ft_dprintf(2, "\n");}
				free(child->token->value);
				child->token->value = ft_strdup((char*)matches->content); // FUCKING MOCHE
				ft_lstdel_value(&matches);
			}
		}
		head = head->next;
	}
	(void)context;
	(void)quotes;
	return (SUCCESS);
}
