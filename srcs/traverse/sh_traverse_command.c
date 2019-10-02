/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 00:35:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/02 09:09:51 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** apply_expansion_to_children
** We apply expansion here for all possible command (grammar) child.
** simple_command, compound_command...
*/
static int	apply_expansion_to_children(t_ast_node *child, t_context *context)
{
	int 		ret;

	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	if ((ret = sh_traverse_tools_browse(child, context)))
		return (ret);
	return (SUCCESS);
}

/*
** compound_and_redirection
** Check what kind of compound command we have and if we have
** redirection_list to apply
*/
static int	compound_and_redirection(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	t_list		*compound_redir;
	int			ret;
	
	child = node->children->content;
	child = child->children->content;
	compound_redir = NULL;
	if (node->children->next)
	{
		context->phase = E_TRAVERSE_PHASE_REDIRECTIONS;
		if ((ret = sh_traverse_tools_browse(node->children->next->content, context)) != SUCCESS)
			return (ret);
		compound_redir = context->redirections;
		context->redirections = NULL;
	}
//	ret = g_grammar[child->symbol->id].traverse(child, context);
	if (child->symbol->id == sh_index(SUBSHELL))
		ret = sh_traverse_subshell(child, context);
	else if (child->symbol->id == sh_index(BRACE_GROUP))
		ret = sh_traverse_brace_group(child, context);
	if (sh_reset_redirection(&compound_redir))
		return (FAILURE);
	return (ret);
}
/*
 * sh_traverse_command
** This is the dispatcher of command (grammar) node
** Just check what type of command we have and call the
** right traverse.
** If we have compound_command (like subshell), we can have some pipe to apply here.
*/
int			sh_traverse_command(t_ast_node *node, t_context *context)
{
	t_ast_node *child;
	int 		ret;

	ret = 0;
	child = node->children->content;
	if ((ret = apply_expansion_to_children(child, context)) != SUCCESS)
		return (ret);
	sh_traverse_tools_show_traverse_start(node, context);//mettre node pour parcourir eventuel redirection
	if (child->symbol->id == sh_index(SIMPLE_COMMAND))
		ret = sh_traverse_simple_command(child, context);
	else if (child->symbol->id == sh_index(COMPOUND_COMMAND))
		ret = compound_and_redirection(node, context);
	if (ret != SUCCESS)
		sh_env_update_ret_value_and_question(context->shell, ret);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
