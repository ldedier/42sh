/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_word_by_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:04:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/21 17:59:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
int		get_word_len(char *s, int index)
{
	int i;

	i = index;
	while (s[i])
	{
		if (ft_isseparator(s[i]))
			return (i - index);
		i++;
	}
	return (i - index);
}

int		process_populate_empty_word(t_word *word)
{
	if (!(word->str = ft_strdup("")))
		return (1);
	word->len = 0;
	word->utf8_len = 0;
	word->index_byte_offset = 0;
	word->index_char_offset = 0;
	return (0);
}

int		process_populate_word_by_index(t_word *word,
		int nb_words, int parse_w, int index)
{
	word->word_index = (parse_w ? nb_words : 0);
	if (!word->word_index)
		word->start_index = index;
	word->prev_word_index = nb_words;
	if (word->word_index)
	{
		word->len = get_word_len(word->to_compare, word->start_index);
		if (!(word->str = ft_strndup(&word->to_compare[word->start_index],
						word->len)))
			return (1);
		word->utf8_len = ft_strlen_utf8(word->str);
	}
	else
		return (process_populate_empty_word(word));
	return (0);
}

void	increment_word(int i, int index, t_word *word, char *str)
{
	word->start_index = i;
	word->index_byte_offset = index - i;
	word->index_char_offset = ft_strnlen_utf8(&str[i], index - i);
}

int		populate_word_by_index(char *s, int index, t_word *word)
{
	int nb_w;
	int parse_w;
	int i;

	i = -1;
	parse_w = 0;
	nb_w = 0;
	word->str = NULL;
	word->to_compare = s;
	while (s[++i])
	{
		if (i == index)
			return (process_populate_word_by_index(word, nb_w, parse_w, index));
		if (!ft_isseparator(s[i]) && !parse_w)
		{
			increment_word(i, index, word, s);
			parse_w = 1;
			nb_w++;
		}
		if (ft_isseparator(s[i]) && parse_w)
			parse_w = 0;
	}
	if (i == index)
		return (process_populate_word_by_index(word, nb_w, parse_w, index));
	return (0);
}

int		populate_word_from_lexer_no_token(t_list **tokens, t_list **prev,
		t_word *word)
{
	t_list	*token_ptr;
	char	*value;
	t_list	*next;

	if (!(value = ft_strdup("")))
		return (sh_perror(SH_ERR1_MALLOC, "get_token_from_lexer_no_token (1)"));
	if (!(token_ptr = t_token_node_new(LEX_TOK_WORD, value)))
	{
		free(value);
		return (sh_perror(SH_ERR1_MALLOC, "get_token_from_lexer (2)"));
	}
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

void	populate_word_from_token(t_word *word, int index)
{
	word->str = word->token->value;
	word->to_compare = word->token->value;
	word->len = ft_strlen(word->str);
	word->utf8_len = ft_strlen_utf8(word->str);
	word->start_index = word->token->index_start;
	word->index_byte_offset = index - word->start_index;
	word->index_char_offset =
		ft_strnlen_utf8(word->str, word->index_byte_offset);
	word->start_index = word->token->index_start;
}

void	populate_word_from_created_token(t_word *word, int index)
{
	word->str = word->token->value;
	word->to_compare = word->token->value;
	word->len = 0;
	word->utf8_len = 0;
	word->start_index = 0;
	word->index_byte_offset = 0;
	word->index_char_offset = 0;
	word->start_index = index;
}

void	print_word(t_word *word)
{
	ft_printf("\nstr: %s\n", word->str);
	ft_printf("to compare: %s\n", word->to_compare);
	ft_printf("len: %d\n", word->len);
	ft_printf("utf8_len: %d\n", word->utf8_len);
	ft_printf("start_index: %d\n", word->start_index);
	ft_printf("index_char_offset: %d\n", word->index_char_offset);
	ft_printf("index_byte_offset: %d\n", word->index_byte_offset);
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
		populate_word_from_created_token(word, index);
	}
	else
	{
		word->token = token;
		populate_word_from_token(word, index);
	}
//	print_word(word);
	return (0);
}

int		populate_parsed_word_by_index(t_shell *shell, char *command,
		int index, t_word *word)
{
	int		ret;
	t_list	*tokens;

	tokens = NULL;
	if ((ret = sh_lexer(command, &tokens, shell)) != SUCCESS)
		return ret;
	if ((ret = populate_word_from_lexer(&tokens, index, word)))
		return (FAILURE);
	if ((ret = sh_parser(tokens, shell)))
		return ret;
	return (ret);
}
