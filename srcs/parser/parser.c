/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 11:55:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol, t_cfg *cfg)
{
	return (symbol->id >= 0 && symbol->id < cfg->nb_terms);
}

void	sh_populate_token(t_token *token, t_symbol_id id,
		int val)
{
	token->lval = val;
	token->id = id;
	token->index = sh_index(id);
	token->value = NULL;
}

int		sh_parse_token_list(t_lr_parser *parser, t_list **tokens,
			t_ast_node **ast_root, t_ast_node **cst_root)
{
	int ret;

	if ((ret = sh_lr_parse(parser, tokens, ast_root, cst_root)) != SUCCESS)
	{
		ft_lstdel(&parser->stack, sh_free_stack_item_lst);
		return (ret);
	}
	else
	{
		if (sh_verbose_ast())
		{
			ft_dprintf(2, "OK !\n");
			ft_dprintf(2, "\nAST:\n");
			sh_print_ast(*ast_root, &parser->cfg, 0);
			ft_dprintf(2, "\nCST:\n");
			sh_print_ast(*cst_root, &parser->cfg, 0);
		}
		ft_lstdel(&parser->stack, sh_free_stack_item_lst_light);
		return (SUCCESS);
	}
}

int		sh_parser(t_shell *shell, t_lr_parser *parser, t_exec *res)
{
	t_token token;
	int		ret;

	sh_populate_token(&token, END_OF_INPUT, 0);
	ft_lstaddnew_last(&res->tokens, &token, sizeof(t_token));
	if (sh_verbose_ast())
	{
		ft_dprintf(2, "input tokens: ");
		sh_print_token_list(res->tokens, &parser->cfg);
	}
	if ((ret = sh_parse_token_list(parser, &res->tokens,
		&res->ast_root, &res->cst_root)) != SUCCESS)
	{
		sh_env_update_ret_value(shell, SH_RET_SYNTAX_ERROR);
	}
	return (ret);
}
