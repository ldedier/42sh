/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lr_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:36:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/22 16:45:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_stack_item	*new_stack_item(t_ast_builder *ast_builder, t_state *state)
{
	t_stack_item *res;

	if (!(res = (t_stack_item *)malloc(sizeof(t_stack_item))))
		return (sh_perrorn(SH_ERR1_MALLOC, "new_stack_item"));
	if (!ast_builder)
	{
		res->stack_enum = E_STACK_STATE_INDEX;
		res->stack_union.state = state;
	}
	else
	{
		res->stack_enum = E_STACK_AST_BUILDER;
		res->stack_union.ast_builder = ast_builder;
	}
	return (res);
}

int				process_lr_parser_ret(t_lr_parser *parser,
	t_action action, t_ast_node **ast_root, t_ast_node **cst_root)
{
	if (action.action_enum == E_ACTION_SHIFT)
	{
		if (sh_process_shift(parser->tmp_tokens,
			action.action_union.state, parser))
		{
			return (FAILURE);
		}
	}
	else if (action.action_enum == E_ACTION_REDUCE)
	{
		if (sh_process_reduce(action.action_union.production, parser,
			ast_root, cst_root))
		{
			return (FAILURE);
		}
	}
	else if (action.action_enum == E_ACTION_ACCEPT)
		return (SUCCESS);
	else if (action.action_enum == E_ACTION_ERROR)
		return (ERROR);
	return (3);
}

int				process_lr_parse(t_lr_parser *parser, t_list **tokens,
		t_ast_node **ast_root, t_ast_node **cst_root)
{
	t_action		action;
	t_stack_item	*stack_item;
	t_token			*token;
	t_state			*state;

	if (parser->stack == NULL)
		return (ERROR);
	stack_item = (t_stack_item *)parser->stack->content;
	if (stack_item->stack_enum != E_STACK_STATE_INDEX)
		return (ERROR);
	else
		state = stack_item->stack_union.state;
	token = (t_token *)(*tokens)->content;
//	ft_printf("CURRENT TOKEN: ");
//	sh_print_token(token, g_glob.cfg);
	action = parser->lr_tables[state->index][token->index];
	return (process_lr_parser_ret(parser, action, ast_root, cst_root));
}

/*
**		return values:
**
** ERROR	-> syntax error
** FAILURE	-> malloc error
*/

int				sh_lr_parse(t_lr_parser *parser, t_list **tokens,
	t_ast_node **ast_root, t_ast_node **cst_root)
{
	t_stack_item	*stack_item;
	int				ret;

//	ft_lstdel(&parser->stack, sh_free_stack_item_lst);
	parser->tmp_tokens = tokens;
	if (!(stack_item = new_stack_item(NULL, parser->states->content)))
		return (FAILURE);
	if (ft_lstaddnew_ptr(&parser->stack, stack_item, sizeof(t_stack_item *)))
	{
		sh_free_stack_item(stack_item);
		return (sh_perror(SH_ERR1_MALLOC, "sh_lr_parse"));
	}
	while (*tokens)
	{
		ret = process_lr_parse(parser, tokens, ast_root, cst_root);
//		ft_printf("\nAST:\n");
//		sh_print_ast(*ast_root, 0);
//		ft_printf("\nCST:\n");
//		sh_print_ast(*cst_root, 0);
		if (ret != 3)
			return (ret);
//		sh_print_parser_state(parser);
	}
	return (ERROR);
}
