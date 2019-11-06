/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:31:28 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/06 05:15:18 by jmartel          ###   ########.fr       */
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
	sh_expansions_pattern_matching(path, (t_list**)regexp_tab->tbl, &matches); //ret value ?
	// need to free path
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
