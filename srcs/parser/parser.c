/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:42:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/27 21:15:11 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_is_term(t_symbol *symbol)
{
	return (symbol->id >= 0 && symbol->id < NB_TERMS);
}

void	sh_populate_token(t_token *token, t_symbol_id id,
		int val)
{
	token->token_union.ival = val;
	token->id = id;
	token->index = sh_index(id);
	token->value = NULL;
}

int		sh_parse_token_list(t_lr_parser *parser)
{
	int ret;

	sh_free_parser_trees(parser);
	if ((ret = sh_lr_parse(parser)) != SUCCESS)
		return (ret);
	else
	{
		if (sh_verbose_ast())
		{
			ft_dprintf(2, "OK !\n");
			ft_dprintf(2, "\nAST:\n");
			sh_print_ast(parser->ast_root, 0);
		}
		return (SUCCESS);
	}
}

/*
** mdaoud:
** Dummy function to check if the command ends with '&'
** Since the grammar is not coherent with the actual execution of this symbol,
**		I can't really process it when it occurs at the end of the command line.
** This SHOULD be replaced by a better and safer function.
*/

static void		check_ampersand_at_eoc(t_list *token_lst)
{
	t_list	*ptr;
	t_token	*tok;

	ptr = token_lst;
	if (token_lst == NULL)
		return ;
	while (ptr->next != NULL)
	{
		tok = (t_token *)ptr->next->content;
		if (tok->id == END_OF_INPUT && (((t_token *)ptr->content)->id == LEX_TOK_AND))
		{
			g_job_ctrl->ampersand_eol = 1;
			return ;
		}
		else
			g_job_ctrl->ampersand_eol = 0;
		ptr = ptr->next;
	}
}

int		sh_parser(t_list *tokens, t_shell *shell)
{
	t_token token;
	int		ret;

	sh_populate_token(&token, END_OF_INPUT, 0);
	ft_lstaddnew_last(&tokens, &token, sizeof(t_token));
	ft_lstdel(&shell->parser.tokens, sh_free_token_lst);
	check_ampersand_at_eoc(tokens);
	if (sh_verbose_ast())
	{
		ft_dprintf(2, "input tokens: ");
		sh_print_token_list(tokens, &shell->parser.cfg);
	}
	shell->parser.tokens = tokens;
	if ((ret = sh_parse_token_list(&shell->parser)) != SUCCESS)
	{
		sh_env_update_ret_value(shell, SH_RET_SYNTAX_ERROR);
//		sh_perror_err("syntax error", NULL);
	}
	return (ret);
}
