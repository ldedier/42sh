/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/21 00:00:37 by jmartel          ###   ########.fr       */
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
	else
		*path = ft_strdup("");
	if (!path)
		return (sh_perror(SH_ERR1_MALLOC, "globbing : init_path (1)"));
	return (SUCCESS);
}

static int	sh_expansions_globbing_matches(t_list **head, t_list *matches)
{
	t_ast_node	*node;

	// if (sh_verbose_globbing() || 1)
	// 	{ft_lstput_fd(matches, 2); ft_dprintf(2, "\n");}
	// ft_lstput_fd(matches, 2); ft_dprintf(2, "\n");
	node = (t_ast_node*)(*head)->content;
	free(node->token->value);
	if (!(node->token->value = ft_strdup((char*)matches->content)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_globbing_matches (1)"));
	matches = matches->next;
	while (matches)
	{
		node = (t_ast_node*)(*head)->content;
		if (!(node = sh_add_word_to_ast(node, matches->content)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_expansions_globbing_matches (2)"));
		(*head) = (*head)->next;
		matches = matches->next;
	}
	ft_lstdel(&matches, NULL);
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
	// Need to see for quote removal
	// need t ofind a solution t go threought every field splited fields, with no repeat for non splitted fields
	// while (head)
	// {
		child = (t_ast_node*)head->content;
		if (child->symbol->id != sh_index(LEX_TOK_WORD)) // Are TERM_WORD only valid tokens ?? Assignment_word ?
		{
			return (SUCCESS);
			// head = head->next;
			// continue ;
		}
		str = child->token->value;
		sh_regexp_parse(str, &regexp_tab);
		if (regexp_tab) //modify
		{
			init_path(&path, str);
			pattern_matching(path, (t_list**)regexp_tab->tbl, quotes, &matches);
			if (matches)
				sh_expansions_globbing_matches(&head, matches);
		}
	// 	head = head->next;
	// }
	(void)context;
	(void)quotes;
	return (SUCCESS);
}
