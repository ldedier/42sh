/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:10:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/09 04:39:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	alias_clean_stack(t_lexer *lexer)
{
	t_list	*head;
	t_list	*prev;

	head = lexer->alias_stack;
	while (head)
	{
		prev = head;
		head = head->next;
		free(prev);
	}
	lexer->alias_stack = NULL;
}

static int	alias_add_stack(t_lexer *lexer, char *value)
{
	t_list	*new;

	if (!(new = ft_lstnew(value, sizeof(char*))))
		return (LEX_FAIL);
	ft_lstadd_last(&(lexer->alias_stack), new);
	return (SUCCESS);
}

static int	alias_check_stack(t_lexer *lexer, char *value)
{
	t_list	*head;

	head = lexer->alias_stack;
	while (head)
	{
		if (value == head->content)
		{
			if (sh_verbose_lexer())
				ft_dprintf(2, RED"\t\trecursive alias detected\n"EOC);
			return (ERROR);
		}
		head = head->next;
	}
	return (SUCCESS);
}

int			sh_lexer_alias(t_lexer *lexer, char *value)
{
	char	*alias;

	if (lexer->tok_len == 0 || lexer->current_id != LEX_TOK_WORD || !lexer->first_word)
		return (LEX_OK);
	if (sh_vars_get_index(lexer->alias, value) == -1)
	{
		alias_clean_stack(lexer);
		return (LEX_OK);
	}
	alias = sh_vars_get_value(lexer->alias, NULL, value);
	if (sh_verbose_lexer())
		ft_dprintf(2, GREEN"\talias detected : (%s) => (%s)\n"EOC, value, alias);
	if (alias_check_stack(lexer, alias))
		return (SUCCESS);
	lexer->input = ft_strrep_free(lexer->input, alias, lexer->tok_start, lexer->tok_len);
	if (!lexer->input)
		return (LEX_FAIL);
	if (sh_verbose_lexer())
		ft_dprintf(2, GREEN"\trestarting detection on new input : %s\n"EOC, lexer->input + lexer->tok_start);
	t_lexer_reset(lexer, lexer->tok_start);
	if (alias_add_stack(lexer, alias))
		return (LEX_FAIL);
	if (ft_strrnstr(alias, " ", 1))
		lexer->first_word = 2;
	return (LEX_CONTINUE);
}