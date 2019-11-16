/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer_arithmetic.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:22:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/15 17:59:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_token	*t_token_integer(int value)
{
	t_token *res;

	if (!(res = malloc(sizeof(t_token))))
		return (NULL);
	res->value = NULL;
	res->index = LEX_TOK_AR_INTEGER;
	res->token_union.ival = value;
	return (res);
}

void	populate_test1(t_list **tokens, t_shell *shell)
{
	t_token *token;

	token = t_token_integer(14);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_new(LEX_TOK_AR_GREAT, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_integer(14);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_PLUS, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_VARIABLE, "a", &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_DEC, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_MULTIPLY, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(14);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_OR, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(14);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
}

void	populate_test2(t_list **tokens, t_shell *shell)
{
	t_token *token;

	token = t_token_integer(1);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_new(LEX_TOK_AR_GREATEQ, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(2);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_LESS, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_integer(1);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
}
void	populate_test3(t_list **tokens, t_shell *shell)
{
	t_token *token;

	token = t_token_integer(42);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_new(LEX_TOK_AR_PLUS, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(1);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_new(LEX_TOK_AR_MULTIPLY, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));

	token = t_token_integer(10);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_new(LEX_TOK_AR_MINUS, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(5);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_new(LEX_TOK_AR_MULTIPLY, NULL, &shell->parser_ar.cfg);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
	token = t_token_integer(2);
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	
}

int		sh_lexer_arithmetic(char *command, t_list **tokens, t_shell *shell)
{
	t_token *token;

	(void)command;
	*tokens = NULL;
	populate_test1(tokens, shell);
//	populate_test2(tokens, shell);
//	populate_test3(tokens, shell);
	token = t_token_new(END_OF_INPUT_AR, NULL, &shell->parser_ar.cfg);	
	ft_lstaddnew_ptr_last(tokens, token, sizeof(t_token *));
	sh_print_token_list(*tokens, &shell->parser_ar.cfg);
	return (SUCCESS);
}
