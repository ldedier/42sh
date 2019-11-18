/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:11:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/18 10:03:03 by ldedier          ###   ########.fr       */
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

void		sh_free_ast_node(t_ast_node **node, int node_to_free)
{
	t_ast_node		*child;
	t_ast_node		*tmp;

	if (!*node)
		return ;
	if ((*node)->token)
		sh_free_token(*node, &(*node)->token);
	while ((*node)->children != NULL)
	{
		child = (t_ast_node *)ft_lstpop_ptr(&(*node)->children);
		sh_free_ast_node(&child, node_to_free);
	}
	tmp = *node;
	if ((*node)->builder)
	{
		if (node_to_free == 1)
			(*node)->builder->ast_node = NULL;
		else if (node_to_free == 2)
			(*node)->builder->cst_node = NULL;
	}
	free(tmp);
	*node = NULL;
}

void		sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(&ast_builder->ast_node, 1);
	sh_free_ast_node(&ast_builder->cst_node, 2);
	free(ast_builder);
}
