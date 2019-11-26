/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 08:17:05 by jmartel          ###   ########.fr       */
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

/*
** -1 in token->lval is here to know nodes that result for globbing, to avoid
**	recursive loops.
*/

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
	node->token->lval = -1;
	matches = matches->next;
	while (matches)
	{
		if (!(node = sh_add_word_to_ast(node, matches->content, g_glob.cfg)))
		{
			return (sh_perror(
				SH_ERR1_MALLOC, "sh_expansions_globbing_matches (2)"));
		}
		node->token->lval = -1;
		matches = matches->next;
	}
	ft_lstdel(&start, NULL);
	ft_dy_tab_empty(quotes);
	return (SUCCESS);
}

static void	clean_non_original_quotes(t_dy_tab *quotes)
{
	int			i;
	t_quote		**tbl;
	int			j;

	tbl = (t_quote**)quotes->tbl;
	i = 0;
	while (tbl[i])
	{
		if (!tbl[i]->is_original)
		{
			ft_strdelchar(tbl[i]->c, 0);
			ft_dy_tab_suppr_index(quotes, i);
			j = i;
			while (tbl[j])
			{
				tbl[j]->index -= 1;
				tbl[j]->c -= 1;
				j++;
			}
		}
		else
			i++;
	}
	return ;
}

/*
** pattern matching (globing) : *, ?, [], !, intervals with '-'
**
**	FAILURE : malloc errors
**	SUCCESS : returned even if no globbinghad been processed, for any reasons
*/

static int	sh_expansions_globbing_process_node(
	t_ast_node *node, t_dy_tab *quotes)
{
	char		*str;
	t_list		*matches;
	t_dy_tab	*regexp_tab;
	char		*path;
	int			ret;

	regexp_tab = NULL;
	matches = NULL;
	str = node->token->value;
	clean_non_original_quotes(quotes);
	if (!ft_strpbrk(str, "?[*"))
		return (SUCCESS);
	if ((ret = sh_glob_lexer(str, &regexp_tab, quotes)) == FAILURE)
		return (FAILURE);
	else if (ret == ERROR)
		return (SUCCESS);
	init_path(&path, str);
	ret = sh_expansions_pattern_matching(
		path, (t_list**)regexp_tab->tbl, &matches);
	if (!ret && matches)
		ret = sh_expansions_globbing_matches(node, matches, quotes);
	t_regexp_free_tab(&regexp_tab);
	return (ret);
}

int			sh_expansions_globbing(t_ast_node *node, t_dy_tab *quotes, int ret)
{
	t_ast_node		*children;
	t_list			*head;
	t_list			*next_head;

	head = node->parent->children;
	children = (t_ast_node*)head->content;
	if (!children || !children->token || children->token->lval == -1)
		return (SUCCESS);
	while (head && !ret)
	{
		children = (t_ast_node*)head->content;
		if (!children || !children->token)
			return (SUCCESS);
		if (children->symbol->id != sh_index(LEX_TOK_WORD))
		{
			head = head->next;
			continue ;
		}
		next_head = head->next;
		if (children && children->token && children->token->lval != -1)
			ret = sh_expansions_globbing_process_node(children, quotes);
		head = next_head;
	}
	return (ret);
}
