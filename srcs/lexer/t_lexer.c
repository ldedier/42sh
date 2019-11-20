/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:39:44 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 13:00:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			t_lexer_init(
	t_lexer *lexer, t_lex_mode mode, t_shell *shell, char *input)
{
	ft_bzero(lexer, sizeof(*lexer));
	if (!(lexer->input = ft_strdup(input)))
		return (FAILURE);
	lexer->shell = shell;
	lexer->env = shell->env;
	lexer->vars = shell->vars;
	lexer->alias = shell->alias;
	lexer->mode = mode;
	t_lexer_reset(lexer, 0);
	lexer->first_word = 1;
	lexer->next_alias_index = -1;
	return (SUCCESS);
}

void		t_lexer_reset(t_lexer *lexer, int tok_start)
{
	lexer->quoted = 0;
	lexer->expansion = 0;
	lexer->tok_start = tok_start;
	lexer->tok_len = 0;
	lexer->current_id = LEX_TOK_UNKNOWN;
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
}

static int	t_lexer_create_and_fill_token(t_lexer *lexer, char *value)
{
	t_list		*link;
	t_token		*token;

	if (!(link = t_token_node_new(lexer->current_id, NULL, g_glob.cfg)))
	{
		free(value);
		return (LEX_FAIL);
	}
	token = link->content;
	token->value = value;
	ft_lstadd_last(&lexer->list, link);
	token->expansion = lexer->expansion;
	token->index_start = lexer->tok_start;
	token->index_end = lexer->tok_start + lexer->tok_len + 1;
	t_lexer_reset(lexer, lexer->tok_start + lexer->tok_len);
	if (sh_verbose_lexer())
	{
		ft_dprintf(2, "new token delimited : ");
		t_token_show(token);
		ft_dprintf(2, "\n");
	}
	return (sh_lexer_reserved_words(lexer, token));
}

/*
** t_lexer_add_token:
**	Use current lexer state to create a new token, appending it at the
**	end of the token list. It use tok_start and tok_len to
**	determine value in input.
**	If lexer state is ok and token value correspond to an alias lexer->input
**	is updated, token is not delimited and lexer is reset at the begining of
**	the current token.
**	If alias resolution failed token is created and encapsuled in a t_list.
**	Token attributes are set using lexer current state.
**	Lexer is then reset and reserved word detection is performed on new token.
**
**	Returned Values:
**		LEX_OK
**		LEX_CONTINUE : alias had been found and token was not delimited
**		LEX_FAIL : malloc error
*/

int			t_lexer_add_token(t_lexer *lexer)
{
	char		*value;
	int			ret;

	if (lexer->tok_len == 0 && lexer->current_id == LEX_TOK_UNKNOWN)
		return (LEX_OK);
	if (!(value = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len)))
		return (LEX_FAIL);
	if ((ret = sh_lexer_alias(lexer, value)) != LEX_OK)
	{
		free(value);
		return (ret);
	}
	return (t_lexer_create_and_fill_token(lexer, value));
}

void		t_lexer_show(t_lexer *lexer)
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
