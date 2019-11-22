/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ar_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:07:33 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 13:38:23 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			t_ar_lexer_init(t_lexer *lexer, t_shell *shell, char *input)
{
	ft_bzero(lexer, sizeof(*lexer));
	lexer->input = input;
	lexer->shell = shell;
	lexer->env = shell->env;
	lexer->vars = shell->vars;
	t_ar_lexer_reset(lexer, 0);
}

void			t_ar_lexer_reset(t_lexer *lexer, int tok_start)
{
	lexer->quoted = 0;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

static void		token_fill_fields(
	t_lexer *lexer, t_token *token, char *value)
{
	token->value = value;
	token->index_start = lexer->tok_start;
	token->index_end = lexer->tok_start + lexer->tok_len + 1;
	token->index = token->id;
	if (lexer->current_id == LEX_TOK_AR_INTEGER)
		token->lval = ft_atol(token->value);
	if (lexer->current_id == LEX_TOK_AR_VARIABLE)
		lexer->first_word = 1;
	if (sh_verbose_expansion())
	{
		ft_dprintf(2, "new token delimited : ");
		t_ar_token_show(token);
		ft_dprintf(2, "\n");
	}
}

/*
**	Returned Values:
**		LEX_OK
**		LEX_FAIL : malloc error
*/

int				t_ar_lexer_add_token(t_lexer *lexer)
{
	t_list		*link;
	t_token		*token;
	char		*value;

	if (lexer->tok_len == 0 && lexer->current_id == LEX_TOK_UNKNOWN)
		return (LEX_OK);
	if (!(value = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len)))
		return (LEX_FAIL);
	if (!(link = t_token_node_new(lexer->current_id, NULL, g_glob.cfg)))
	{
		free(value);
		return (LEX_FAIL);
	}
	token = link->content;
	ft_lstadd_last(&lexer->list, link);
	token_fill_fields(lexer, token, value);
	t_ar_lexer_reset(lexer, lexer->tok_start + lexer->tok_len);
	return (LEX_OK);
}

void			t_ar_lexer_show(t_lexer *lexer)
{
	t_list	*head;

	head = lexer->list;
	while (head)
	{
		t_ar_token_show((t_token*)head->content);
		if (head->next)
			ft_putstr_fd(" -> ", 2);
		head = head->next;
	}
	ft_putstr_fd("\n", 2);
}
