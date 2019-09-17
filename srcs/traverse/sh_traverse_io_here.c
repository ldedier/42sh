/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/09 10:56:17 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char			*heredoc_dash(const char *str)
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

static int		sh_traverse_io_here_interactive(t_ast_node *node,
		t_context *context, char *(*heredoc_func)(const char *))
{
	t_ast_node		*child;
	char			*heredoc_res;
	int				ret;
	t_heredoc		heredoc_data;

	child = (t_ast_node *)node->children->content;
	heredoc_data.func = heredoc_func;
	heredoc_data.stop = child->token->value;
	heredoc_data.apply_expansion = &(child->token->apply_heredoc_expansion);
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

int				sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	t_redirection	*redirection;

	redirection = &node->metadata.heredoc_metadata.redirection;
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
		return (sh_traverse_io_here_phase_interactive(node, context));
	else if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
		return (sh_traverse_io_here_phase_expansion(
					redirection, node, context));
	else if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		if (sh_add_redirection(redirection->type,
				redirection->redirected_fd, redirection->fd,
					&context->current_command_node
						->metadata.command_metadata.redirections))
			return (FAILURE);
	}
	return (SUCCESS);
}
