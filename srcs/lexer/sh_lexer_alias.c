/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_alias.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:10:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/16 15:52:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	alias_add_stack(t_lexer *lexer, char *value)
{
	t_list	*new;

	if (!(new = ft_lstnew(value, sizeof(char*))))
		return (sh_perror(SH_ERR1_MALLOC, "alias_add_stack"));
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
	char			*alias;

	if (lexer->tok_len == 0 || lexer->current_id != LEX_TOK_WORD
		|| !lexer->first_word || lexer->mode == E_LEX_AUTOCOMPLETION)
		return (LEX_OK);
	if (sh_vars_get_index(lexer->alias, value) == -1)
		return (LEX_OK);
	alias = sh_vars_get_value(lexer->alias, NULL, value);
	if (sh_verbose_lexer())
		ft_dprintf(2, GREEN"\talias detected : (%s)=>(%s)\n"EOC, value, alias);
	if (alias_check_stack(lexer, alias))
		return (SUCCESS);
	if (!(lexer->input =
		ft_strrep_free(lexer->input, alias, lexer->tok_start, lexer->tok_len)))
		return (LEX_FAIL);
	lexer->next_alias_index = lexer->tok_start + ft_strlen(alias);
	t_lexer_reset(lexer, lexer->tok_start);
	if (alias_add_stack(lexer, alias))
		return (LEX_FAIL);
	if (ft_strrnstr(alias, " ", 1))
		lexer->first_word = 2;
	return (LEX_CONTINUE);
}
