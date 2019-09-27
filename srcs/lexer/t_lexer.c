/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:39:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/25 06:53:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	t_lexer_init(t_lexer *lexer, int tok_start)
{
	lexer->quoted = 0;
	lexer->expansion = 0;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

int		t_lexer_add_token(t_lexer *lexer)
{
	t_list		*link;
	t_token		*token;

	if (lexer->tok_len == 0 && lexer->current_id == LEX_TOK_UNKNOWN)
	{
		t_lexer_init(lexer, lexer->tok_start + lexer->tok_len);
		return (LEX_OK);
	}
	if (!(link = t_token_node_new(lexer->current_id, NULL)))
		return (LEX_FAIL);
	token = link->content;
	ft_lstadd_last(&lexer->list, link);
	token->value = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len);
	if (!token->value)
	{
		free(token);
		free(link);
		return (LEX_FAIL);
	}
	token->expansion = lexer->expansion;
	token->index_start = lexer->tok_start;
	token->index_end = lexer->tok_start + lexer->tok_len;
	t_lexer_init(lexer, lexer->tok_start + lexer->tok_len);
	return (LEX_OK);
}

void	t_lexer_show(t_lexer *lexer)
{
	t_list	*head;

	head = lexer->list;
	while (head)
	{
		t_token_show((t_token*)head->content);
		if (head->next)
			ft_putstr_fd(" -> ", 2);
		head = head->next;
	}
	ft_putstr_fd("\n", 2);
}
