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

// void	sh_free_redirection(void *red, size_t dummy)
// {
// 	t_redirection *redirection;

// 	(void)dummy;
// 	redirection = (t_redirection *)red;
// 	if (!redirection->closed)
// 		close(redirection->fd);
// 	free(redirection);
// }

// static void	sh_free_ast_node_meta(t_ast_node **node)
// {
// 	if ((*node)->symbol->id == sh_index(SIMPLE_COMMAND))
// 	{
// 		ft_lstdel(&(*node)->metadata.command_metadata.redirections,
// 			sh_free_redirection);
// 	}
// 	else if ((*node)->symbol->id == sh_index(PIPE_SEQUENCE))
// 		ft_lstdel(&(*node)->metadata.pipe_metadata.contexts,
// 			sh_free_context_dup_lst);
// }

/*
** free a node and update the builder if it should to indicate that
** the data has already been freed
*/

void	sh_free_ast_node(t_ast_node **node, int update)
{
	t_ast_node		*child;
	t_ast_builder	*builder;

	if (!*node)
		return ;
	if ((*node)->token)
		sh_free_token(*node, &(*node)->token);
	// sh_free_ast_node_meta(node);
	while ((*node)->children != NULL)
	{
		child = (t_ast_node *)ft_lstpop_ptr(&(*node)->children);
		sh_free_ast_node(&child, update);
	}
	if (update && (builder = (*node)->builder))
	{
		if (builder->ast_node == *node)
			builder->ast_node = NULL;
		else
			builder->cst_node = NULL;
	}
	free(*node);
	*node = NULL;
}

void	sh_free_ast_builder(t_ast_builder *ast_builder)
{
	sh_free_ast_node(&ast_builder->ast_node, 0);
	sh_free_ast_node(&ast_builder->cst_node, 0);
	free(ast_builder);
}
