/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_reserved_words.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 01:28:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/06 01:32:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		sh_lexer_close_brace(t_token *token, int *brace)
{
	if (ft_strequ(token->value, "}"))	
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Rbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_RBRACE, token);
		brace = 0;
	}
}

static int		sh_lexer_is_reserved(t_token *token, t_list **head, int *brace)
{
	if (ft_strequ(token->value, "!"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Bang\n"EOC, token->value);
		t_token_update_id(LEX_TOK_BANG, token);
		*head = (*head)->next;
		return (1);
	}
	else if (ft_strequ(token->value, "{"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Lbrace\n"EOC, token->value);
		t_token_update_id(LEX_TOK_LBRACE, token);
		*head = (*head)->next;
		*brace = 1;
		return (1);
	}
	return (0);
}

static int		sh_lexer_is_operator(t_symbol_id id, t_list **head)
{
	if (id == LEX_TOK_LESS || id == LEX_TOK_GREAT
		|| (LEX_TOK_DLESS <= id &&  id <= LEX_TOK_CLOBBER))
	{
		*head = (*head)->next;
		if ((*head))
			*head = (*head)->next;
		return (1);
	}
	return (0);
}

static int		sh_lexer_is_assignment(t_token *token, t_list **head)
{
	if (token->id == LEX_TOK_ASSIGNMENT_WORD) // let it until rule8 will be updated
	{
		*head = (*head)->next;
		return (1);
	}
	if (sh_expansions_variable_valid_name(token->value))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, RED"%s : Assignment word\n"EOC, token->value);
		t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
		*head = (*head)->next;
		return (1);
	}
	return (0);
}

int				sh_lexer_reserved_words(t_lexer *lexer)
{
	t_list	*head;
	t_token	*token;
	int		first_word;
	int		brace;

	head = lexer->list;
	first_word = 1;
	brace = 0;
	while (head)
	{
		token = (t_token*)head->content;
		if (token->id == LEX_TOK_AND || token->id ==LEX_TOK_SEMICOL || token->id == LEX_TOK_AND_IF || token->id == LEX_TOK_OR_IF)
			first_word = 1;
		else if (token->id == LEX_TOK_CLS_PAR || token->id == LEX_TOK_OPN_PAR)
			first_word = 1;
		else if (!first_word && brace && token->id == LEX_TOK_WORD)
			sh_lexer_close_brace(token, &brace);
		else if (first_word)
		{
			if (sh_lexer_is_reserved(token, &head, &brace))
				continue ;
			else if (sh_lexer_is_operator(token->id, &head))
				continue ;
			else if (ft_strchr(token->value, '=') && sh_lexer_is_assignment(token, &head))
				continue ;
			else
				first_word = 0;
		}
		head = head->next;
	}
	return (SUCCESS);
}
