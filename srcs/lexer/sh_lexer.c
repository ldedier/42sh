/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:11:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:56:24 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_lexer_run_rules(t_lexer *lexer)
{
	int				ret;
	int				i;
	static int		(*rules[LEX_RULES_LEN]) (t_lexer *) = {
		&sh_lexer_rule1, &sh_lexer_rule2, &sh_lexer_rule3, &sh_lexer_rule4,
		&sh_lexer_rule5, &sh_lexer_rule6, &sh_lexer_rule7, &sh_lexer_rule8,
		&sh_lexer_rule9, &sh_lexer_rule10 };

	i = 0;
	if (sh_verbose_lexer())
		ft_dprintf(2, CYAN"lexer in progress on :%.2c\n"EOC, lexer->c);
	while ((ret = rules[i](lexer)) == LEX_CONTINUE && i < LEX_RULES_LEN)
		i++;
	if (sh_verbose_lexer())
		ft_dprintf(2, COLOR_GREEN"\trule %2d applied\n"COLOR_END, i + 1);
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
	if (lexer->alias_stack && lexer->next_alias_index >= 0
		&& lexer->next_alias_index < lexer->tok_start + lexer->tok_len)
	{
		lexer->next_alias_index = -1;
		ft_lstdel(&lexer->alias_stack, NULL);
	}
	return (ret);
}

int				sh_lexer_error_ret_value(t_lexer *lexer, int ret)
{
	t_token_free_list(&lexer->list);
	if (ret == ERROR)
	{
		if (lexer->mode != E_LEX_AUTOCOMPLETION)
			return (sh_perror_err("lexical error", NULL));
		return (ERROR);
	}
	else if (ret == CTRL_C)
		sh_env_update_ret_value(lexer->shell, SH_RET_SIG_RECEIVED + SIGINT);
	else if (ret == CTRL_D)
	{
		sh_env_update_ret_value(lexer->shell, 2);
		return (ERROR);
	}
	return (ret);
}

int				sh_lexer(char *input, t_list **tokens, t_shell *shell,
		t_lex_mode mode)
{
	t_lexer		lexer;
	int			ret;

	lexer.mode = mode;
	if (t_lexer_init(&lexer, mode, shell, input))
		return (FAILURE);
	ret = LEX_OK;
	while (ret == LEX_OK)
		ret = sh_lexer_run_rules(&lexer);
	free(lexer.input);
	ft_lstdel(&lexer.alias_stack, NULL);
	if (ret != LEX_END)
		return (sh_lexer_error_ret_value(&lexer, ret));
	if (sh_verbose_lexer())
		t_lexer_show(&lexer);
	if (sh_verbose_lexer())
		t_lexer_show(&lexer);
	*tokens = lexer.list;
	return (SUCCESS);
}
