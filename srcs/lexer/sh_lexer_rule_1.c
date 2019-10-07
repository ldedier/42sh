/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:25:15 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 04:16:10 by jmartel          ###   ########.fr       */
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
		{
			ft_dprintf(2, "unexpected EOF while looking for matching %c\n",
				lexer->quoted);
			return (LEX_FAIL);
		}
	}
	if (lexer->quoted == '\"' || lexer->quoted == '\'')
	{
		if (!(lexer->input = ft_strjoin_free(lexer->input, "\n", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_lexer_rule1_process_quoted"));
	}
	else if (lexer->backslash)
		lexer->backslash = 0;
	return (SUCCESS);
}

static int	sh_lexer_rule1_process_quoted(t_lexer *lexer)
{
	static int	reading = 1;
	t_gnl_info	info;
	int			gnl_ret;

	if ((gnl_ret = sh_lexer_rule1_process_quoted_start(lexer, reading)))
		return (gnl_ret);
	gnl_ret = get_next_line2(0, &info, 1);
	if (!(lexer->input = ft_strjoin_free(lexer->input, info.line, 1)))
	{
		free(info.line);
		return (sh_perror(SH_ERR1_MALLOC, "sh_lexer_rule1_process_quoted"));
	}
	free(info.line);
	if (gnl_ret == 0)
	{
		if (!lexer->input || !*(lexer->input))
			return (LEX_END);
		reading = 0;
	}
	else if (gnl_ret == -1)
		return (sh_perror2("rule1", "lexer", "get_next_line2 error"));
	return (LEX_OK);
}

int			sh_lexer_rule1(t_lexer *lexer)
{
	if (lexer->c == '\0')
	{
		if (lexer->quoted > 0 || lexer->backslash)
		{
			if (!isatty(0) || lexer->mode == E_LEX_AUTOCOMPLETION)
				return (sh_lexer_rule1_process_quoted(lexer));
			else
				return (sh_process_quoted(lexer));
		}
		if (t_lexer_add_token(lexer))
			return (LEX_FAIL);
		sh_lexer_reserved_words(lexer, t_lexer_get_last_token(lexer)); // ret value
		return (LEX_END);
	}
	return (LEX_CONTINUE);
}
