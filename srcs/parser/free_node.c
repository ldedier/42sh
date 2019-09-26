/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 12:54:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_free_token(t_ast_node *node, t_token **token)
{
	if (*token)
	{
		free((*token)->value);
		(*token)->value = NULL;
		free(*token);
		(*token) = NULL;
		if (node->relative)
			node->relative->token = NULL;
	}
}

/*
** free a node and update the builder if it should to indicate that
** the data has already been freed
*/

void	sh_free_ast_node(t_ast_node **node, int update)
{
	t_ast_node		*child;

	if (!*node)
		return ;
	if ((*node)->token)
		sh_free_token(*node, &(*node)->token);
	while ((*node)->children != NULL)
	{
		child = (t_ast_node *)ft_lstpop_ptr(&(*node)->children);
		sh_free_ast_node(&child, update);
	}
//	ft_printf("freeing node:\n");
//	sh_print_ast(*node, 0);
	if (update)
	{
		(*node)->builder->ast_node = NULL;
		(*node)->builder->cst_node = NULL;
	}
	free(*node);
	*node = NULL;
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	static int i = 0;
	(void)ast_builder;
	(void)i;
//	ft_printf("freeing from ast_builder %d\n", ++i);
	sh_free_ast_node(&ast_builder->ast_node, 0);
	sh_free_ast_node(&ast_builder->cst_node, 0);
	free(ast_builder);
//	ft_printf("end of freeing from ast_builder %d\n", i);
}
