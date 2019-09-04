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

static int	loop_expansion(char **str, t_context *context)
{
	int	start_expansion;
	int ret;

	start_expansion = 0;
	while ((*str)[start_expansion])
	{
		if ((*str)[start_expansion] == '\\'
			&& ((*str)[start_expansion + 1] == '$' || (*str)[start_expansion + 1] == '\\'))
		{
			ft_strcpy(*str + start_expansion, (*str) + start_expansion + 1);
			start_expansion++;
		}
		if ((*str)[start_expansion] == '$' && (*str)[start_expansion + 1] != '\n')
		{
			if ((ret = sh_expansions_process(str, (*str) + start_expansion, context, &start_expansion)) != SUCCESS)
			{
				if (sh_env_update_ret_value_and_question(context->shell, ret))
				{
					free(*str);
					return (FAILURE);
				}
			}
		}
		else
			start_expansion++;
	}
	return (SUCCESS);
}

static int		sh_traverse_io_here_interactive(t_redirection **redirection,
		t_ast_node *node, t_context *context,
			char *(*heredoc_func)(const char *))
{
	t_ast_node		*first_child;
	char			*heredoc_res;
	int				ret;
	t_heredoc		heredoc_data;

(void)redirection;
	first_child = (t_ast_node *)node->children->content;
	heredoc_data.func = heredoc_func;
	heredoc_data.stop = first_child->token->value;
	heredoc_data.apply_expansion = &(first_child->token->apply_heredoc_expansion);
	if (!(heredoc_res = get_heredoc(context, &heredoc_data, &ret)))
		return (ret);
	if (ret == CTRL_D)
		ret = sh_traverse_io_here_interactive_ctrl_d(first_child, context);
	if (ret != FAILURE)
	{
		free(first_child->token->value);
		first_child->token->value = heredoc_res;
	}
	else
		free(heredoc_res);
	return (ret);
}

int				sh_traverse_io_here(t_ast_node *node, t_context *context)
{
	t_ast_node		*first_child;
	char			*(*heredoc_func)(const char *);
	t_redirection	*redirection;
	int				fds[2];

	redirection = &node->metadata.heredoc_metadata.redirection;
	if (context->phase == E_TRAVERSE_PHASE_INTERACTIVE_REDIRECTIONS)
	{
		first_child = node->children->content;
		g_glob.command_line.interrupted = 1;
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
	else if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		first_child = node->children->next->content;
		first_child = first_child->children->content;
		if (first_child->token->apply_heredoc_expansion)
		{
			if (loop_expansion(&(first_child->token->value), context) != SUCCESS)
				return (FAILURE);
		}	
		if (pipe(fds))
			return (sh_perror(SH_ERR1_PIPE, "sh_traverse_io_here_end"));
		else
		{
			redirection->type = INPUT;
			redirection->redirected_fd = context->redirected_fd;
			redirection->fd = fds[0];
			ft_putstr_fd(first_child->token->value, fds[1]);
			close(fds[1]);
		}
	}
	return (SUCCESS);
}
