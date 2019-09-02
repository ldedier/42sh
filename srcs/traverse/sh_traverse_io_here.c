/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/02 16:35:11 by jmartel          ###   ########.fr       */
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

static char		*get_heredoc(t_context *context, char *eof,
		char *(*heredoc_func)(const char *), int *ret)
{
	if (isatty(0))
		return (heredoc(context->shell, eof, heredoc_func, ret));
	else
		return (heredoc_canonical_mode(context->shell, eof, heredoc_func, ret));
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

static int		sh_traverse_io_here_interactive(t_redirection **redirection,
		t_ast_node *node, t_context *context,
			char *(*heredoc_func)(const char *))
{
	t_ast_node		*first_child;
	char			*heredoc_res;
	int				ret;
	int				fds[2];

	first_child = (t_ast_node *)node->children->content;
	if (!(heredoc_res = get_heredoc(context, first_child->token->value,
			heredoc_func, &ret)))
		return (ret);
	if (ret == CTRL_D)
		ret = sh_traverse_io_here_interactive_ctrl_d(first_child, context);
	if (ret != FAILURE && pipe(fds))
		ret = sh_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end");
	(*redirection)->type = INPUT;
	(*redirection)->redirected_fd = context->redirected_fd;
	if (ret != FAILURE)
	{
		(*redirection)->fd = fds[0];
		ft_putstr_fd(heredoc_res, fds[1]);
		close(fds[1]);
	}
	free(heredoc_res);
	return (ret);
}

int				sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	char			*(*heredoc_func)(const char *);
	t_redirection	*redirection;

	redirection = &node->metadata.heredoc_metadata.redirection;
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		g_glob.command_line.interrupted = 1;
		first_child = node->children->content;
		if (first_child->symbol->id == sh_index(LEX_TOK_DLESSDASH))
			heredoc_func = &heredoc_dash;
		else
			heredoc_func = &ft_strdup;
		return (sh_traverse_io_here_interactive(&redirection,
				node->children->next->content, context, heredoc_func));
	}
	else if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		if (sh_add_redirection(sh_new_redir(redirection->type,
				redirection->redirected_fd, redirection->fd),
					&context->current_command_node
						->metadata.command_metadata.redirections))
			return (FAILURE);
	}
	return (SUCCESS);
}
