/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer_rule_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:43:58 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 13:41:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	rule_5_is_valid_op_first_char(char c)
{
	if (c == '&'
	|| c == '|'
	|| c == '+'
	|| c == '-'
	|| c == '*'
	|| c == '/'
	|| c == '%'
	|| c == '<'
	|| c == '>'
	|| c == '!'
	|| c == '=')
		return (1);
	return (0);
}

static void	rule5_set_token_id_one_len(t_lexer *lexer, char *value)
{
	if (value[0] == '+')
		lexer->current_id = LEX_TOK_AR_PLUS;
	else if (value[0] == '-')
		lexer->current_id = LEX_TOK_AR_MINUS;
	else if (value[0] == '*')
		lexer->current_id = LEX_TOK_AR_MULTIPLY;
	else if (value[0] == '/')
		lexer->current_id = LEX_TOK_AR_DIVIDE;
	else if (value[0] == '%')
		lexer->current_id = LEX_TOK_AR_MODULO;
	else if (value[0] == '<')
		lexer->current_id = LEX_TOK_AR_LESS;
	else if (value[0] == '>')
		lexer->current_id = LEX_TOK_AR_GREAT;
}

int			sh_ar_lexer_rule_5(t_lexer *lexer)
{
	int		ret;
	char	*buff;

	if (rule_5_is_valid_op_first_char(lexer->c))
	{
		ret = t_ar_lexer_add_token(lexer);
		lexer->tok_len += 1;
		rule5_set_token_id_one_len(lexer, lexer->input + lexer->tok_start);
		if (lexer->current_id == LEX_TOK_AR_PLUS
			|| lexer->current_id == LEX_TOK_AR_MINUS)
		{
			buff = lexer->input + lexer->tok_start + lexer->tok_len;
			if (buff[0] == lexer->c && (ft_isalpha(buff[1]) || buff[1] == '_'))
				lexer->first_word = 1;
		}
		return (ret);
	}
	return (LEX_CONTINUE);
}
