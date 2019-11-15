/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:57:03 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/21 15:24:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_add_to_list_child_ast_builder(
		t_ast_builder *child_ast_builder, t_production *production,
		t_lr_parser *parser)
{
	if (sh_is_replacing(child_ast_builder, &parser->cfg)
			&& child_ast_builder->symbol == production->from
			&& !*parser->tmp_replacing_ast_node)
	{
		*parser->tmp_replacing_ast_node = child_ast_builder->ast_node;
		free(child_ast_builder);
	}
	else
	{
		if (ft_lstaddnew_ptr(parser->tmp_ast_builder_list, child_ast_builder,
			sizeof(t_ast_builder *)))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	sh_treat_relevance_in_reduce(
		t_ast_builder *child_ast_builder, t_production *production,
		t_lr_parser *parser)
{
	if (child_ast_builder->symbol->relevant)
	{
		if (sh_process_add_to_list_child_ast_builder(child_ast_builder,
					production, parser))
			return (FAILURE);
	}
	else
	{
		free(child_ast_builder->ast_node);
		free(child_ast_builder);
	}
	return (SUCCESS);
}

static int	sh_process_process_reduce(t_lr_parser *parser,
				t_production *production)
{
	t_stack_item	*stack_item;
	t_ast_builder	*child_ast_builder;

	ft_lstpop(&parser->stack);
	if (!(stack_item = ft_lstpop_ptr(&parser->stack)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
	child_ast_builder = stack_item->stack_union.ast_builder;
	child_ast_builder->cst_node->builder = NULL;
	child_ast_builder->ast_node->builder = NULL;
	if (ft_lstaddnew_ptr(&(*parser->tmp_cst_root)->children,
				child_ast_builder->cst_node, sizeof(t_ast_node *)))
	{
		free(stack_item);
		return (sh_perror(SH_ERR1_MALLOC, "sh_process_reduce_pop"));
	}
	child_ast_builder->cst_node->parent = *parser->tmp_cst_root;
	if (sh_treat_relevance_in_reduce(child_ast_builder, production, parser))
	{
		free(stack_item);
		return (FAILURE);
	}
	free(stack_item);
	return (SUCCESS);
}

int			sh_process_reduce_pop(t_production *production,
				t_lr_parser *parser, t_list **ast_builder_list,
					t_ast_node **replacing_ast_node)
{
	int				length;

	parser->tmp_ast_builder_list = ast_builder_list;
	parser->tmp_replacing_ast_node = replacing_ast_node;
	length = ft_lstlen(production->symbols);
	while (length)
	{
		if (sh_process_process_reduce(parser, production))
			return (FAILURE);
		length--;
	}
	return (SUCCESS);
}
