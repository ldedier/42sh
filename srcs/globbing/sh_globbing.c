/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/06 04:12:50 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	check_for_final_slash(t_list *regexp_list, t_dirent *dirent)
{
	t_regexp	*regexp;

	regexp = (t_regexp*)regexp_list->content;
	if (regexp->type != REG_FINAL_SLASH)
		return (SUCCESS);
	else if (!(DT_DIR == dirent->d_type))
		return(ERROR);
	return (SUCCESS);
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
	while (head)
	{
		if (ft_strcmp((char*)head->content, (char*)new->content) > 0)
			break ;
		prev = head;
		head = head->next;
	}
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
		return (ERROR); // perrror ? permissions 
	while ((dirent = readdir(dir)))
	{
		if (check_for_final_slash(*regexp_list, dirent))
			continue ;
		if (sh_verbose_globbing())
			ft_dprintf(2, "working on path : %s/%s\n", path, dirent->d_name);
		if (sh_is_pattern_matching(dirent->d_name, *regexp_list) == SUCCESS)
		{
			new_path = ft_strjoin_path(path, dirent->d_name); //protect && leaks
			if (new_path && ((t_regexp*)(*regexp_list)->content)->type == REG_FINAL_SLASH)
				new_path = ft_strjoin_free(new_path, "/", 1);
			if (!new_path)
				return (sh_perror(SH_ERR1_MALLOC, "pattern_matching")); // leaks ??
			// ft_dprintf(2, "path : %s || new path : %s\n", path, new_path);
			if (regexp_list[1])
			{
				if (sh_verbose_globbing())
					ft_dprintf(2, "recursive call : %s\n", new_path);
				pattern_matching(new_path, regexp_list + 1, quotes, matchs);
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
	}
	return (SUCCESS);
}

static int	init_path(char **path, char *str)
{
	if (*str == '/')
		*path = ft_strdup("/");
	else
		*path = ft_strdup("");
	if (!path)
		return (sh_perror(SH_ERR1_MALLOC, "globbing : init_path (1)"));
	return (SUCCESS);
}

static int	sh_expansions_globbing_matches(t_ast_node *node, t_list *matches)
{
	// sh_expansions_globbing_matches_sort(matches);
	free(node->token->value);
	if (!(node->token->value = ft_strdup((char*)matches->content)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_globbing_matches (1)"));
	matches = matches->next;
	while (matches)
	{
		if (!(node = sh_add_word_to_ast(node, matches->content)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_globbing_matches (2)"));
		matches = matches->next;
	}
	ft_lstdel(&matches, NULL); // need to free content ??
	return (SUCCESS);
}

static void	free_regexp_tab(t_dy_tab **regexp_tab)
{
	int			i;
	t_list		**list_tab;

	i = 0;
	list_tab = (t_list**)(*regexp_tab)->tbl;
	while (list_tab[i])	
	{
		ft_lstdel(list_tab + i, &t_regexp_free);
		i++;
	}
	ft_dy_tab_del_ptr(*regexp_tab);
	*regexp_tab = NULL;
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
*/

int			sh_expansions_globbing(t_context *context, t_ast_node *node, t_dy_tab *quotes)
{
	char		*str;
	t_list		*matches;
	t_dy_tab	*regexp_tab;
	char		*path;
	int			ret;

	regexp_tab = NULL;
	matches = NULL;
	// Need to see for quote removal
	// need t ofind a solution t go threought every field splited fields, with no repeat for non splitted fields
	str = node->token->value;
	if (!ft_strpbrk(str, "?[*"))
		return (SUCCESS);
	if ((ret = sh_regexp_parse(str, &regexp_tab)))// leaks ?
		return (ret);
	init_path(&path, str);
	pattern_matching(path, (t_list**)regexp_tab->tbl, quotes, &matches); //ret value ?
	if (matches)
	{
		if (sh_verbose_globbing())
		{ft_lstput_fd(matches, 2);ft_dprintf(2, "\n");}
		sh_expansions_globbing_matches(node, matches);
		ft_dy_tab_empty(quotes);
	}
	free_regexp_tab(&regexp_tab);
	(void)context;
	(void)quotes;
	return (SUCCESS);
}
