/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ar_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:23:01 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 12:23:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_ar_lexer_run_rules(t_lexer *lexer)
{
	int				ret;
	int				i;
	static int		(*rules[9]) (t_lexer *) = {
		&sh_ar_lexer_rule_1,
		&sh_ar_lexer_rule_2,
		&sh_ar_lexer_rule_3,
		&sh_ar_lexer_rule_4,
		&sh_ar_lexer_rule_5,
		&sh_ar_lexer_rule_6,
		&sh_ar_lexer_rule_7,
		&sh_ar_lexer_rule_8,
		&sh_ar_lexer_rule_9 };

	i = 0;
	if (sh_verbose_expansion())
		ft_dprintf(2, CYAN"ar_lexer in progress on :%.2c\n"EOC, lexer->c);
	while ((ret = rules[i](lexer)) == LEX_CONTINUE && i < 9)
		i++;
	if (sh_verbose_expansion())
		ft_dprintf(2, COLOR_GREEN"\trule %2d applied\n"COLOR_END, i + 1);
	lexer->c = lexer->input[lexer->tok_start + lexer->tok_len];
	return (ret);
}

int			sh_ar_lexer(char *expansion, t_list **tokens, t_shell *shell)
{
	t_lexer		lexer;
	int			ret;

	t_ar_lexer_init(&lexer, shell, expansion);
	ret = LEX_OK;
	while (ret == LEX_OK)
		ret = sh_ar_lexer_run_rules(&lexer);
	if (ret != LEX_END)
	{
		t_token_free_list(&lexer.list);
		return (ret);
	}
	if (sh_verbose_expansion())
		t_ar_lexer_show(&lexer);
	*tokens = lexer.list;
	return (SUCCESS);
}
