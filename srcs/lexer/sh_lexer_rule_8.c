/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:45:02 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/03 16:38:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_lexer_rule8_assignment(t_lexer *lexer)
{
	char	*buff;
	t_token	*tok;
	t_list	*head;

	if (lexer->quoted)
		return (SUCCESS);
	buff = ft_strndup(lexer->input + lexer->tok_start, lexer->tok_len + 1);
	if (!buff)
		return (FAILURE);
	if (sh_expansions_variable_valid_name(buff))
	{
		head = lexer->list;
		while (head && head->next)
			head = head->next;
		if (head)
			tok = (t_token*)head->content;
		else
			tok = NULL;
		if (!tok || tok->id == LEX_TOK_ASSIGNMENT_WORD
		|| tok->id == LEX_TOK_AND_IF || tok->id == LEX_TOK_OR_IF
		|| tok->id == LEX_TOK_SEMICOL)
			lexer->current_id = LEX_TOK_ASSIGNMENT_WORD;
	}
	free(buff);
	return (SUCCESS);
}

int		sh_lexer_rule8(t_lexer *lexer)
{
	if (lexer->current_id == LEX_TOK_WORD
	|| lexer->current_id == LEX_TOK_ASSIGNMENT_WORD)
	{
		lexer->tok_len++;
		return (LEX_OK);
	}
	return (LEX_CONTINUE);
		if (lexer->c == '=')
			sh_lexer_rule8_assignment(lexer);
}
