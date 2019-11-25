/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:15 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 03:11:56 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_lexer_rule1_process_quoted_start(t_lexer *lexer, int reading)
{
	if (!reading || lexer->mode == E_LEX_AUTOCOMPLETION)
	{
		if (lexer->mode == E_LEX_AUTOCOMPLETION)
			return (LEX_ERR);
		else if (lexer->quoted)
			return (sh_perror_unexpected_eof(lexer));
	}
	if (lexer->quoted)
	{
		if (!(lexer->input = ft_strjoin_free(lexer->input, "\n", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_lexer_rule1_process_quoted"));
	}
	else if (lexer->backslash)
		lexer->backslash = 0;
	if (lexer->quoted == '|')
		lexer->quoted = '\0';
	return (SUCCESS);
}

static int	sh_lexer_rule1_process_quoted(t_lexer *lexer)
{
	static int	reading = 1;
	t_gnl_info	info;
	int			ret;

	if ((ret = sh_lexer_rule1_process_quoted_start(lexer, reading)))
		return (ret);
	ret = get_next_line2(0, &info, 1);
	if (!(lexer->input = ft_strjoin_free(lexer->input, info.line, 1)))
	{
		free(info.line);
		return (sh_perror(SH_ERR1_MALLOC, "sh_lexer_rule1_process_quoted"));
	}
	free(info.line);
	if (ret == 0)
	{
		if (!lexer->input || !*(lexer->input))
			return (LEX_END);
		reading = 0;
	}
	else if (ret == -1)
		return (sh_perror2("rule1", "lexer", "get_next_line2 error"));
	return (LEX_OK);
}

static int	sh_lexer_rule1_check_final_pipe(t_lexer *lexer)
{
	t_list		*head;
	t_list		*last_pipe;

	head = lexer->list;
	last_pipe = NULL;
	while (head)
	{
		if (((t_token*)head->content)->id == LEX_TOK_WORD)
		{
			last_pipe = NULL;
		}
		else if (((t_token*)head->content)->id == LEX_TOK_PIPE)
		{
			last_pipe = head;
		}
		head = head->next;
	}
	if (!last_pipe || lexer->mode == E_LEX_AUTOCOMPLETION)
		return (SUCCESS);
	lexer->quoted = '|';
	return (ERROR);
}

/*
** sh_lexer_rule1:
**	posix : 1. If the end of input is recognized,
**			the current token (if any) shall be delimited.
**	Rule 1 is checking that quotes are correctly closed before terminating
**	lexer process. Unclosed quotes treatment is different if in interactive
**	mode or not.
**	If any token had been started it is delimited and added to list.
**	If t_lexer_add_token return LEX_CONTINUE an alias had been detected,
**	lexer state had been reset and it shall start a new lexer cycle.
**
**	Returned Values :
**		LEX_END : Successfully finished lexer process
**		LEX_OK : Alias had been detected, need to start new lexer cycles
**		LEX_CONTINUE : Current char is not input end
**		LEX_FAIL : malloc error
*/

int			sh_lexer_rule1(t_lexer *lexer)
{
	int		ret;

	if (lexer->c == '\0')
	{
		if (lexer->quoted > 0 || lexer->backslash)
		{
			if (!isatty(0) || lexer->mode == E_LEX_AUTOCOMPLETION)
				return (sh_lexer_rule1_process_quoted(lexer));
			return (sh_process_quoted(lexer));
		}
		if ((ret = t_lexer_add_token(lexer)) == LEX_FAIL)
			return (ret);
		else if (ret == LEX_CONTINUE)
			return (LEX_OK);
		if (sh_lexer_rule1_check_final_pipe(lexer))
		{
			lexer->quoted = '|';
			if (!isatty(0) || lexer->mode == E_LEX_AUTOCOMPLETION)
				return (sh_lexer_rule1_process_quoted(lexer));
			return (sh_process_quoted(lexer));
		}
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}
