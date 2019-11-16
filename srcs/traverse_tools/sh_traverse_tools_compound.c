/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_tools_compound.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:23:48 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/16 09:05:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	get_last_separator(t_ast_node *curr_node)
{
	t_ast_node	*last_separator;

	g_job_ctrl->ampersand_eol = 0;
	if (curr_node->children->next)
	{
		last_separator = curr_node->children->next->content;
		last_separator = last_separator->children->content;
		if (last_separator->symbol->id == sh_index(SEPARATOR_OP))
		{
			last_separator = last_separator->children->content;
			if (last_separator->symbol->id == sh_index(LEX_TOK_AND))
			{
				g_job_ctrl->ampersand_eol = 1;
			}
			else if (last_separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
				g_job_ctrl->ampersand_eol = 0;
		}
	}
}

/*
** search_term
** compound_list node can be a newline_list follow by a term node and separator
** need to have at least a term node.
**
** So we skip all newline_list to go to the term node.
** Have to check of the proper separator.
** A term can be a list of and_or break by separator node.
** A separator can be ';' '&' 'line_break' or 'newline_list'
*/

long		sh_traverse_tools_search_term(
		t_ast_node *node, t_context *context)
{
	t_list		*el;
	int			ret;
	t_ast_node	*curr_node;

	el = node->children;
	ret = SUCCESS;
	while (el)
	{
		curr_node = el->content;
		if (curr_node->symbol->id == sh_index(COMPOUND_LIST))
		{
			get_last_separator(curr_node);
			el = curr_node->children;
			curr_node = el->content;
		}
		if (curr_node->symbol->id == sh_index(TERM))
		{
			break ;
		}
		el = el->next;
	}
	if (el)
		ret = get_node_to_exec(
				curr_node, context, SEPARATOR, &sh_get_separator);
	return (ret);
}

long		sh_traverse_tools_compound_redir(
		t_ast_node *node, t_context *context,
		t_ast_node **compound_redir, t_list **lst_redi)
{
	int			ret;

	if (node->parent->parent->children->next)
		*compound_redir = node->parent->parent->children->next->content;
	else
		*compound_redir = NULL;
	if ((ret = loop_traverse_compound_redirection(*compound_redir, context)))
		return (ret);
	*lst_redi = context->redirections;
	context->redirections = NULL;
	return (ret);
}
