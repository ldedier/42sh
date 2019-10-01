/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/01 16:55:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_lexer_final_check:
**	Check that any unknown token is present, send an error if any is founc,
**	to avoid sending it to parser.
**
**	Returned Values:
**		LEX_OK : Assignment word changed, no unknown token found.
**		LEX_ERR : unknown / unidentified token found
*/

static int		sh_lexer_final_check(t_lexer *lexer)
{
	t_list	*head;
	t_token	*token;

	head = lexer->list;
	if (!head || !head->content)
		return (LEX_OK);
	while (head)
	{
		token = (t_token*)head->content;
		if (token->id == LEX_TOK_UNKNOWN)
			return (sh_perror_err("lexer", "Unknow token detected"));
		head = head->next;
	}
	return (LEX_OK);
}

static void		sh_lexer_close_brace(t_token *token, int *brace)
{
	if (ft_strequ(token->value, "}"))	
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, "Rbrace token detected\n");
		t_token_update_id(LEX_TOK_RBRACE, token);
		brace = 0;
	}
}

static int		sh_lexer_is_reserved(t_token *token, t_list **head, int *brace)
{
	if (ft_strequ(token->value, "!"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, "Bang token detected\n");
		t_token_update_id(LEX_TOK_BANG, token);
		*head = (*head)->next;
		return (1);
	}
	else if (ft_strequ(token->value, "{"))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, "Lbrace token detected\n");
		t_token_update_id(LEX_TOK_LBRACE, token);
		*head = (*head)->next;
		*brace = 1;
		return (1);
	}
	return (0);
}

static int		sh_lexer_is_operator(t_symbol_id id, t_list **head)
{
	if (id == LEX_TOK_LESS || id == LEX_TOK_GREAT
		|| (LEX_TOK_DLESS <= id &&  id <= LEX_TOK_CLOBBER))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, "Operator found\n");
		*head = (*head)->next;
		if ((*head))
			*head = (*head)->next;
		return (1);
	}
	return (0);
}

static int		sh_lexer_is_assignment(t_token *token, t_list **head)
{
	if (token->id == LEX_TOK_ASSIGNMENT_WORD) // let it until rule8 will be updated
	{
		*head = (*head)->next;
		return (1);
	}
	if (sh_expansions_variable_valid_name(token->value))
	{
		if (sh_verbose_lexer())
			ft_dprintf(2, "Assignment word found\n");
		t_token_update_id(LEX_TOK_ASSIGNMENT_WORD, token);
		*head = (*head)->next;
		return (1);
	}
	return (0);
}

static int		sh_lexer_reserved_words(t_lexer *lexer)
{
	t_list	*head;
	t_token	*token;
	int		first_word;
	int		brace;

	head = lexer->list;
	first_word = 1;
	brace = 0;
	while (head)
	{
		token = (t_token*)head->content;
		if (sh_verbose_lexer())
		{
			ft_dprintf(2, RED"token : %s\n"EOC, token->value);
			ft_dprintf(2, RED"\tfirst : %d || brace : %d\n"EOC, first_word, brace);
		}
		if (token->id == LEX_TOK_AND || token->id ==LEX_TOK_SEMICOL)
			first_word = 1;
		else if (!first_word && brace && token->id == LEX_TOK_WORD)
			sh_lexer_close_brace(token, &brace);
		else if (first_word)
		{
			if (sh_lexer_is_reserved(token, &head, &brace))
				continue ;
			else if (sh_lexer_is_operator(token->id, &head))
				continue ;
			else if (ft_strchr(token->value, '=') && sh_lexer_is_assignment(token, &head))
				continue ;
			else
				first_word = 0;
		}
		head = head->next;
	}
	return (SUCCESS);
}

static int		sh_lexer_run_rules(t_lexer *lexer)
{
	int				ret;
	int				i;
	static int		(*rules[LEX_RULES_LEN]) (t_lexer *) = {
		&sh_lexer_rule1,
		&sh_lexer_rule2,
		&sh_lexer_rule3,
		&sh_lexer_rule4,
		&sh_lexer_rule5,
		&sh_lexer_rule6,
		&sh_lexer_rule7,
		&sh_lexer_rule8,
		&sh_lexer_rule9,
		&sh_lexer_rule10 };

	i = 0;
	if (sh_verbose_lexer())
		ft_dprintf(2, CYAN"lexer in progress on :%.2c\n"EOC, lexer->c);
	while ((ret = rules[i](lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
		i++;
	if (sh_verbose_lexer())
		ft_dprintf(2, COLOR_GREEN"\trule %2d applied\n"COLOR_END, i + 1);
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
	return (ret);
}

int				sh_lexer(char *input, t_list **tokens, t_shell *shell,
		t_lex_mode mode)
{
	t_lexer		lexer;
	int			ret;

	ft_bzero(&lexer, sizeof(t_lexer));
	lexer.mode = mode;
	lexer.shell = shell;
	if (!(lexer.input = ft_strdup(input)))
		return (FAILURE);
	t_lexer_init(&lexer, 0);
	lexer.env = shell->env;
	lexer.vars = shell->vars;
	ret = LEX_OK;
	while (ret == LEX_OK)
		ret = sh_lexer_run_rules(&lexer);
	free(lexer.input);
	if (ret != LEX_END)
	{
		t_token_free_list(&lexer.list);
		if (ret == ERROR)
			return (sh_perror_err("lexical error", NULL));
		else if (ret == CTRL_C)
			sh_env_update_ret_value(shell, SH_RET_SIG_RECEIVED + SIGINT);
		else if (ret == CTRL_D)
			sh_env_update_ret_value(shell, 2);
		return (ret);
	}
	if (sh_verbose_lexer())
		t_lexer_show(&lexer);
	ret = sh_lexer_reserved_words(&lexer);
	ret = sh_lexer_final_check(&lexer);
	if (sh_verbose_lexer())
		t_lexer_show(&lexer);
	*tokens = lexer.list;
	return (ret);
	// ret = sh_lexer_reserved_words(&lexer);
}
