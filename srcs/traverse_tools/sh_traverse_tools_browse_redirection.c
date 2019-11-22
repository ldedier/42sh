/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_browse_redirection.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:32:45 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/22 13:07:50 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_ast_node	*to_simple_command(t_ast_node *node)
{
	t_list	*lst;

	lst = node->children;
	while (node->symbol->id != sh_index(SIMPLE_COMMAND))
	{
		node = lst->content;
		lst = node->children;
	}
	return (node);
}

static int			find_cmd_tokens(t_ast_node *child, t_context *context)
{
	int	ret;

	ret = SUCCESS;
	if (child->symbol->id == sh_index(CMD_SUFFIX)
			|| child->symbol->id == sh_index(CMD_PREFIX))
	{
		if ((ret = sh_traverse_tools_browse_redirection(
						child, context)))
		{
			if (sh_reset_redirection(&(context->redirections)))
				return (FAILURE);
			return (ret);
		}
	}
	return (ret);
}

int					loop_traverse_redirection(t_ast_node *node,
	t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	ret = SUCCESS;
	node = to_simple_command(node);
	while (context->phase <= E_TRAVERSE_PHASE_EXECUTE)
	{
		ptr = node->children;
		while (ptr)
		{
			child = ptr->content;
			if ((ret = find_cmd_tokens(child, context)))
				return (ret);
			ptr = ptr->next;
		}
		context->phase += 1;
	}
	return (ret);
}

int					loop_traverse_compound_redirection(
		t_ast_node *node, t_context *context)
{
	int	ret;

	ret = SUCCESS;
	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	while (context->phase <= E_TRAVERSE_PHASE_EXECUTE)
	{
		if ((ret = sh_traverse_tools_browse_redirection(node, context)))
		{
			if (sh_reset_redirection(&(context->redirections)) != SUCCESS)
				return (FAILURE);
			return (ret);
		}
		context->phase += 1;
	}
	return (ret);
}

long				sh_traverse_tools_browse_redirection(
		t_ast_node *node, t_context *context)
{
	t_list		*ptr;
	t_ast_node	*child;
	int			ret;

	if (node == NULL)
		return (SUCCESS);
	ptr = node->children;
	ret = SUCCESS;
	while (ptr != NULL)
	{
		child = ptr->content;
		if ((ret = g_grammar[child->symbol->id].traverse(child, context)))
			break ;
		if (child->children
				&& (ret = sh_traverse_tools_browse_redirection(child, context)))
			break ;
		ptr = ptr->next;
	}
	return (ret);
}
