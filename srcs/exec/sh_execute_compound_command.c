/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_compound_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:16:20 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/10/22 11:51:40 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	get_last_separator(t_ast_node *curr_node)
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
				return (1);
			}
			else if (last_separator->symbol->id == sh_index(LEX_TOK_SEMICOL))
				g_job_ctrl->ampersand_eol = 0;
		}
		else
			return (ERROR);
			/*ft_printf("-well this is a separtor not yet manage like linebreak or something ..-\n");// delete it*/
	}
	return (0);
}

static int	search_term(t_ast_node *node, t_context *context)
{
	t_list		*el;
	int			ret;
	t_ast_node	*curr_node;
	// t_ast_node	*node_to_exec;

	el = node->children;
	// ft_dprintf(g_term_fd, "%sSubshell pid: %d%s\n",COL_MAGENTA, getpid(), EOC);
	// node_to_exec = NULL;
	ret = SUCCESS;
	while (el)
	{
		curr_node = el->content;
		if (curr_node->symbol->id == sh_index(COMPOUND_LIST))
		{
			get_last_separator(curr_node);//check retrun value to know if they are '&' at the end
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
	{
		ret = get_node_to_exec(curr_node, context, SEPARATOR, &sh_get_separator);
	}
	return (ret);
}

int	sh_execute_compound_command(t_ast_node *node, t_context *context)
{
	int			ret;
	t_ast_node	*compound_redir;
	t_list		*lst_redi;

	if (node->parent->parent->children->next)
		compound_redir = node->parent->parent->children->next->content;
	else
		compound_redir = NULL;
	if ((ret = loop_traverse_compound_redirection(compound_redir, context)))
	{
		if (sh_post_execution())
			return (FAILURE);
		return (ret);
	}
	lst_redi = context->redirections;
	context->redirections = NULL;
	sh_traverse_tools_show_traverse_start(node, context);
	ret = search_term(node, context);
	if (sh_reset_redirection(&lst_redi))
		return (FAILURE);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
