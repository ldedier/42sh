/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_word_by_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:04:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 03:25:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		populate_word_from_lexer_no_token(t_list **tokens, t_list **prev,
		t_word *word)
{
	t_list	*token_ptr;
	t_list	*next;

	if (!(token_ptr = t_token_node_new(LEX_TOK_WORD, "", g_glob.cfg)))
		return (sh_perror(SH_ERR1_MALLOC, "get_token_from_lexer (2)"));
	if (*prev == NULL)
	{
		token_ptr->next = *tokens;
		*tokens = token_ptr;
	}
	else
	{
		next = (*prev)->next;
		(*prev)->next = token_ptr;
		token_ptr->next = next;
	}
	word->token = token_ptr->content;
	return (0);
}

int		populate_word_from_token(t_word *word, int index)
{
	if (!(word->str = ft_strdup(word->token->value)))
		return (FAILURE);
	if (!(word->to_compare = ft_strdup(word->token->value)))
	{
		free(word->str);
		return (FAILURE);
	}
	word->len = ft_strlen(word->str);
	word->utf8_len = ft_strlen_utf8(word->str);
	word->start_index = word->token->index_start;
	word->index_byte_offset = index - word->start_index;
	word->index_char_offset =
		ft_strnlen_utf8(word->str, word->index_byte_offset);
	word->start_index = word->token->index_start;
	return (SUCCESS);
}

int		populate_word_from_created_token(t_word *word, int index)
{
	if (!(word->str = ft_strdup(word->token->value)))
		return (FAILURE);
	if (!(word->to_compare = ft_strdup(word->token->value)))
	{
		free(word->str);
		return (FAILURE);
	}
	word->len = 0;
	word->utf8_len = 0;
	word->start_index = 0;
	word->index_byte_offset = 0;
	word->index_char_offset = 0;
	word->start_index = index;
	return (SUCCESS);
}

int		populate_word_from_lexer(t_list **tokens, int index, t_word *word)
{
	t_list	*prev;
	t_token *token;
	int		ret;

	if (!(token = sh_get_token_by_index(*tokens, index, &prev)))
	{
		if ((ret = populate_word_from_lexer_no_token(tokens, &prev, word)))
			return (ret);
		return (populate_word_from_created_token(word, index));
	}
	else
	{
		word->token = token;
		return (populate_word_from_token(word, index));
	}
	return (0);
}

int		populate_parsed_word_by_index(t_shell *shell, char *command,
		int index, t_exec *exec)
{
	int			ret;

	exec->ast_root = NULL;
	exec->cst_root = NULL;
	exec->tokens = NULL;
	if ((ret = sh_lexer(command, &exec->tokens,
		shell, E_LEX_AUTOCOMPLETION)) != SUCCESS)
	{
		exec->word.str = NULL;
		return (ret);
	}
	if (!ret)
		ret = populate_word_from_lexer(&exec->tokens, index, &exec->word);
	if (!ret)
		ret = sh_parser(shell, &shell->parser, exec);
	if (ret == FAILURE)
	{
		ft_lstdel(&exec->tokens, sh_free_token_lst);
		exec->ast_root = NULL;
		exec->cst_root = NULL;
	}
	return (ret);
}
