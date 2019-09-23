/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/24 00:49:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static char		*heredoc_dash(const char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '\t')
		i++;
	return (ft_strdup(&str[i]));
}

/*
** available return for heredoc() :
**		FAILURE (malloc error)
**		CTRL_D
**		CTRL_C
*/

static int		sh_traverse_io_here_interactive_ctrl_d(
	t_ast_node *first_child, t_context *context)
{
	ft_dprintf(2, "%s: warning: here-document delimited by end of file "
		"(wanted `%s\')\n", SH_NAME, first_child->token->value);
	if (sh_env_update_ret_value_and_question(context->shell, SH_RET_ERROR))
		return (FAILURE);
	return (SUCCESS);
}

// Unactivated quote removal for expansion rework
// Need to use previous quote removal version in that case

static int		sh_traverse_io_here_interactive(t_ast_node *node,
		t_context *context, char *(*heredoc_func)(const char *))
{
	t_ast_node		*child;
	char			*heredoc_res;
	int				ret;
	t_heredoc		heredoc_data;

	child = (t_ast_node *)node->children->content;
	heredoc_data.func = heredoc_func;
	heredoc_data.apply_expansion = &(child->token->apply_heredoc_expansion);
	if (ft_strpbrk(child->token->value, "\"\'\\"))
	{
		sh_expansions_quote_removal_in_str(child->token->value);
		(*heredoc_data.apply_expansion) = 0;
	}
	heredoc_data.stop = child->token->value;
	if (!(heredoc_res = get_heredoc(context, &heredoc_data, &ret)))
		return (ret);
	if (ret == CTRL_D)
		ret = sh_traverse_io_here_interactive_ctrl_d(child, context);
	if (ret != FAILURE)
	{
		free(child->token->value);
		child->token->value = heredoc_res;
	}
	else
		free(heredoc_res);
	return (ret);
}

static int		sh_traverse_io_here_phase_interactive(
		t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	char			*(*heredoc_func)(const char *);

	first_child = node->children->content;
	g_glob.command_line.interrupted = 1;
	if (first_child->symbol->id == sh_index(LEX_TOK_DLESSDASH))
		heredoc_func = &heredoc_dash;
	else
		heredoc_func = &ft_strdup;
	return (sh_traverse_io_here_interactive(node->children->next->content,
				context, heredoc_func));
}

//si on rentre dans E_TRAVERSE_PHASE_REDIRECTION on est au niveau de simple command. On peux set un redirection
//dans context
int				sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	// t_redirection	*redirection;
	t_ast_node 		*first_child;
	int				ret;

	// redirection = NULL;
	sh_traverse_tools_show_traverse_start(node, context);
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		ret = sh_traverse_io_here_phase_interactive(node, context);
	else if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		ret = sh_traverse_io_here_phase_expansion(
					/*redirection,*/ node, context);
	}
	else if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		first_child = node->children->next->content;
		first_child = first_child->children->content;
		ret = sh_traverse_tools_io_here_redirection(first_child, context);
	}
	else
		ret = sh_traverse_tools_browse(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
