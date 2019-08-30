/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_here.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/31 19:16:53 by jmartel          ###   ########.fr       */
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

static char		*get_heredoc(t_context *context, char **stop,
		char *(*heredoc_func)(const char *), int *ret)
{
	int 			do_expansion;
	char 			*str;

	do_expansion = 1;
	if (ft_strchr(*stop, '\'') || ft_strchr(*stop, '\"') || ft_strchr(*stop, '\\'))
	{
		do_expansion = 0;
		if ((*ret = sh_scan_expansions(stop, 0, do_expansion, context)) != SUCCESS)
			return (NULL);
	}
	if (isatty(0))
		str = heredoc(context->shell, *stop, heredoc_func, ret);
		// return (heredoc(context->shell, *stop, heredoc_func, ret));
	else
		str = heredoc_canonical_mode(context->shell, *stop, heredoc_func, ret);
		// return (heredoc_canonical_mode(context->shell, *stop, heredoc_func, ret));
	if (*ret == SUCCESS && do_expansion)
		ft_printf("faut appliquer expansion...\n");
	return (str);
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
	ft_dprintf(2, "21sh: warning: here-document delimited by end of file "
		"(wanted `%s\')\n", first_child->token->value);
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
	if (!(heredoc_res = get_heredoc(context, &(first_child->token->value), heredoc_func, &ret)))
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
