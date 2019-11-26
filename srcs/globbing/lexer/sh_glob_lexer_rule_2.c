/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_glob_lexer_rule_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 07:46:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 07:53:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	verbose_rule_2(t_glob_lexer *lexer)
{
	if (sh_verbose_globbing())
	{
		dprintf(2, GREEN"\tparsed => ");
		t_regexp_show_list(lexer->regexp_tab->tbl[lexer->regexp_tab_index]);
	}
}

static int	add_final_slash(t_list **regexp_tab, int i)
{
	t_regexp	*regexp;
	t_list		*lst;

	if (!(regexp = malloc(sizeof(*regexp))))
		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (1)"));
	if (!(lst = ft_lstnew(regexp, sizeof(*regexp))))
	{
		free(regexp);
		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (2)"));
	}
	regexp->type = REG_FINAL_SLASH;
	regexp->len = 0;
	regexp->value = NULL;
	lst->content = regexp;
	lst->next = regexp_tab[i];
	regexp_tab[i] = lst;
	return (SUCCESS);
}

int			sh_glob_lexer_rule_2(t_glob_lexer *lexer)
{
	t_list	**regexp_list;

	if (lexer->c == '/')
	{
		regexp_list =
			&((t_list**)lexer->regexp_tab->tbl)[lexer->regexp_tab_index];
		if (t_glob_lexer_add_str(lexer))
			return (LEX_FAIL);
		lexer->tok_start += 1;
		if (!lexer->input[lexer->tok_start])
		{
			if (add_final_slash(
				(t_list**)lexer->regexp_tab->tbl, lexer->regexp_tab_index))
				return (sh_perror(SH_ERR1_MALLOC, "sh_glob_lexer_rule_2 (1)"));
		}
		else if (*regexp_list)
		{
			verbose_rule_2(lexer);
			if (ft_dy_tab_add_ptr(lexer->regexp_tab, NULL))
				return (sh_perror(SH_ERR1_MALLOC, "sh_glob_lexer_rule_2 (2)"));
			lexer->regexp_tab_index += 1;
		}
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
}
