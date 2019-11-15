/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_rule_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:37:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 05:49:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_lexer_exp(t_lexer *lexer)
{
	char	*start;
	int		end;

	start = lexer->input + lexer->tok_start + lexer->tok_len;
	if (start[0] == '`')
		end = sh_expansions_cmd_subst_detect_backquotes(start);
	else if (ft_strnstr(start, "<(", 2))
		end = sh_expansions_proc_subst_out_detect(start);
	else if (ft_strnstr(start, ">(", 2))
		end = sh_expansions_proc_subst_in_detect(start);
	else if (ft_strnstr(start, "$(", 2))
		end = sh_expansions_cmd_subst_detect_dollar(start);
	else if (ft_strnstr(start, "${", 2))
		end = sh_expansions_parameter_detect(start);
	else if (start[0] == '$')
	{
		end = sh_expansions_variable_detect(start);
		return (LEX_CONTINUE);
	}
	else
		return (LEX_CONTINUE);
	if (end == -1)
	{
		if (start[0] == '<' || start[0] == '>' || start[1] == '(')
			lexer->quoted = '(';
		else if (start[1] == '{')
			lexer->quoted = '{';
		else if (start[0] == '`')
			lexer->quoted = '`';
		sh_perror_unexpected_eof(lexer);
		if (!isatty(0))
			return (FAILURE);
		sh_env_update_ret_value(lexer->shell, 2);
		return (CTRL_D);
	}
	else if (end == 0)
		return (LEX_CONTINUE);
	lexer->expansion = '$';
	lexer->tok_len += end;
	return (LEX_OK);
}

int				sh_lexer_rule5(t_lexer *lexer)
{
	if (lexer->quoted == '\'' || lexer->quoted == '\\')
		return (LEX_CONTINUE);
	if (lexer->c == '$' || lexer->c == '`' || lexer->c == '<' || lexer->c == '>')
	{
		if (lexer->current_id == LEX_TOK_UNKNOWN)
			lexer->current_id = LEX_TOK_WORD;
		if (lexer->current_id != LEX_TOK_WORD)
			return (LEX_CONTINUE);
		return (sh_lexer_exp(lexer));
	}
	return (LEX_CONTINUE);
}
