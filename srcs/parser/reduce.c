/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/21 15:24:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_reduce_add_to_stack(t_lr_parser *parser,
			t_production *production, t_ast_builder *ast_builder,
				t_ast_node **ast_root)
{
	t_state			*state;
	int				state_from_index;
	t_stack_item	*stack_item;

	stack_item = (t_stack_item *)parser->stack->content;
	state_from_index = stack_item->stack_union.state->index;
	state = parser->lr_tables[state_from_index]
		[production->from->id].action_union.state;
	*ast_root = ast_builder->ast_node;
	if (sh_process_shift_adds(parser, ast_builder, state))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_reduce_add_to_ast(t_list *ast_builder_list,
				t_ast_builder *ast_builder, t_production *production,
					t_lr_parser *parser)
{
	t_ast_builder	*child_ast_builder;

	while (ast_builder_list != NULL)
	{
		child_ast_builder = (t_ast_builder *)ft_lstpop_ptr(&ast_builder_list);
		if (ft_lstaddnew_ptr_last(&ast_builder->ast_node->children,
				child_ast_builder->ast_node, sizeof(t_ast_node *)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_process_reduce"));
		child_ast_builder->ast_node->parent = ast_builder->ast_node;
		free(child_ast_builder);
	}
	if (sh_process_reduce_add_to_stack(parser, production, ast_builder,
			parser->tmp_ast_root))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_reduce(t_production *production, t_lr_parser *parser,
				t_ast_node **ast_root, t_ast_node **cst_root)
{
	t_list			*ast_builder_list;
	t_ast_builder	*ast_builder;
	t_ast_node		*replacing_ast_node;

	replacing_ast_node = NULL;
	ast_builder_list = NULL;
	ast_builder = sh_new_ast_builder(NULL, production->from);
	*cst_root = ast_builder->cst_node;
	parser->tmp_ast_root = ast_root;
	parser->tmp_cst_root = cst_root;
	if (sh_process_reduce_pop(production, parser, &ast_builder_list,
				&replacing_ast_node))
		return (FAILURE);
	if (replacing_ast_node)
	{
		free(ast_builder->ast_node);
		ast_builder->ast_node = replacing_ast_node;
		ast_builder->ast_node->builder = ast_builder;
	}
	return (sh_process_reduce_add_to_ast(ast_builder_list, ast_builder,
			production, parser));
}
