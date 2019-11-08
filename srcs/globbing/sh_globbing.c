/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/07 05:31:35 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

static int	sh_expansions_globbing_matches(
	t_ast_node *node, t_list *matches, t_dy_tab *quotes)
{
	t_list	*start;

	if (sh_verbose_globbing())
	{
		ft_lstput_fd(matches, 2);
		ft_dprintf(2, "\n");
	}
	start = matches;
	free(node->token->value);
	node->token->value = (char*)matches->content;
	matches = matches->next;
	while (matches)
	{
		if (!(node = sh_add_word_to_ast(node, matches->content)))
		{
			return (sh_perror(
				SH_ERR1_MALLOC, "sh_expansions_globbing_matches (2)"));
		}
		matches = matches->next;
	}
	ft_lstdel(&start, NULL);
	ft_dy_tab_empty(quotes);
	return (SUCCESS);
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
**
**	FAILURE : malloc errors
**	SUCCESS : returned even if no globbinghad been processed, for any reasons
*/

// Need to see for quote removal
// Go throught every field splited fields, with no repeat for non splitted field

int			sh_expansions_globbing(t_ast_node *node, t_dy_tab *quotes)
{
	char		*str;
	t_list		*matches;
	t_dy_tab	*regexp_tab;
	char		*path;
	int			ret;

	regexp_tab = NULL;
	matches = NULL;
	str = node->token->value;
	if (!ft_strpbrk(str, "?[*"))
		return (SUCCESS);
	if ((ret = sh_regexp_parse(str, &regexp_tab)) == FAILURE)// leaks ?
		return (ret);
	else if (ret == ERROR)
		return (SUCCESS);
	init_path(&path, str);
	ret = sh_expansions_pattern_matching(
		path, (t_list**)regexp_tab->tbl, &matches);
	free(path);
	if (ret == FAILURE)
		return (FAILURE);
	if (matches)
		sh_expansions_globbing_matches(node, matches, quotes);
	t_regexp_free_tab(&regexp_tab);
	return (SUCCESS);
}
