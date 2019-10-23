/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 00:35:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/22 18:54:20 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** apply_expansion_to_children
** We apply expansion here for all possible redirection of 
** the command (grammar)
*/
static int	apply_expansion_to_children(t_list *lst_child, t_context *context)
{
	t_ast_node	*child;
	int 		ret;

	while (lst_child)
	{
		child = lst_child->content;
		context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
		if ((ret = sh_traverse_tools_browse(child, context)))
			return (ret);
		lst_child = lst_child->next;
	}
	return (SUCCESS);
}

/*
** compound_and_redirection
** Check what kind of compound command we have and if we have
** redirection_list to apply
*/
void handle_int(int digno);
static int	compound_and_redirection(t_ast_node *node, t_context *context)
{
	t_ast_node	*child;
	int			ret;
	
	child = node->children->content;
	child = child->children->content;
	if (node->children->next)
	{
		if ((ret = apply_expansion_to_children(node->children->next, context)) != SUCCESS)
			return (ret);
	}
	if (sh_pre_execution())
		return (FAILURE);
	if (child->symbol->id == sh_index(SUBSHELL))
		ret = sh_traverse_subshell(child, context);
	else if (child->symbol->id == sh_index(BRACE_GROUP))
	{
		signal(SIGINT, handle_int);
		ret = sh_execute_compound_command(child, context);
	}
	if (sh_post_execution())
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
