/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:01:51 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 06:54:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			sh_init_ast_node(t_ast_node *node,
			t_token *token, t_symbol *symbol, t_ast_node *relative)
{
	node->children = NULL;
	node->parent = NULL;
	node->symbol = symbol;
	node->token = token;
	if (token)
		token->ast_node = node;
	node->relative = relative;
}

void			sh_init_ast_nodes(t_ast_builder *ast_builder,
			t_token *token, t_symbol *symbol)
{
	sh_init_ast_node(ast_builder->cst_node,
		token, symbol, ast_builder->ast_node);
	sh_init_ast_node(ast_builder->ast_node,
		token, symbol, ast_builder->cst_node);
	ast_builder->ast_node->builder = ast_builder;
	ast_builder->cst_node->builder = ast_builder;
}

t_ast_builder	*sh_new_ast_builder(t_token *token, t_symbol *symbol)
{
	t_ast_builder *res;

	if (!(res = (t_ast_builder *)malloc(sizeof(t_ast_builder))))
		return (NULL);
	res->symbol = symbol;
	if (!(res->ast_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res);
		return (NULL);
	}
	if (!(res->cst_node = (t_ast_node *)malloc(sizeof(t_ast_node))))
	{
		free(res->ast_node);
		free(res);
		return (NULL);
	}
	sh_init_ast_nodes(res, token, symbol);
	return (res);
}

int				sh_is_replacing(t_ast_builder *ast_builder, t_cfg *cfg)
{
	return (ast_builder->symbol->replacing == 1
		|| sh_is_term(ast_builder->symbol, cfg));
}
