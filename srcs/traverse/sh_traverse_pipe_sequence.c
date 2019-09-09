/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_pipe_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/09 10:54:46 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

//sh_add_pipe_rediretion only for pipe
static int		sh_add_pipe_redirections(t_ast_node *from, t_ast_node *to)
{
	int				fds[2];
	/*t_redirection	redir;*/

	if (pipe(fds))
		return (sh_perror(SH_ERR1_PIPE, "add_pipe_redirections"));
	/*
	 *redir.type = OUTPUT;
	 *redir.redirected_fd = 1;
	 *redir.closed = 0;
	 *redir.fd = fds[PIPE_IN];
	 */
	//add a t_pipe et non a redirection
	if (sh_add_redirection(OUTPUT, 1, fds[PIPE_IN],
				&from->metadata.command_metadata.redirections))
		return (FAILURE);
	/*
	 *if (sh_add_redirection(redir,
	 *    &from->metadata.command_metadata.redirections))
	 *    return (FAILURE);
	 */
	/*
	 *redir.closed = 0;
	 *redir.type = INPUT;
	 *redir.redirected_fd = 0;
	 *redir.fd = fds[PIPE_OUT];
	 */
	if (sh_add_redirection(INPUT, 0, fds[PIPE_OUT],
				&to->metadata.command_metadata.redirections))
		return (FAILURE);
	/*
	 *if (sh_add_redirection(redir, &to->metadata.command_metadata.redirections))
	 *    return (FAILURE);
	 */
	return (SUCCESS);
}

static void		sh_init_command_redirections_list(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*child;

	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		child = ptr->content;
		((t_ast_node *)(child->children->content))
			->metadata.command_metadata.redirections = NULL;
		((t_ast_node *)(child->children->content))
			->metadata.command_metadata.should_exec = 1;
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
}

//here we skip what is not a pipe
static int		sh_process_pipe_redirections(t_ast_node *node)
{
	t_list		*ptr;
	t_ast_node	*from;
	t_ast_node	*to;
	int			ret;

	ptr = (t_list *)node->children;
	from = NULL;
	while (ptr != NULL)
	{
		to = ((t_ast_node *)(ptr->content))->children->content;
		if (from != NULL && (ret = sh_add_pipe_redirections(from, to)))
			return (ret);
		if ((ptr = ptr->next))
			ptr = ptr->next;
		from = to;
	}
	return (SUCCESS);
}

static int		sh_traverse_pipe_sequences_redirections(t_ast_node *node,
		t_context *context)
{
	t_ast_node	*from;
	t_ast_node	*simple_command_node;
	t_list		*ptr;
	int			ret;

	sh_init_command_redirections_list(node);
	if ((ret = sh_process_pipe_redirections(node)))
		return (ret);
	ptr = (t_list *)node->children;
	while (ptr != NULL)
	{
		from = (t_ast_node *)(ptr->content);
		simple_command_node = from->children->content;
		context->current_command_node = simple_command_node;
		if ((ret = g_grammar[from->symbol->id].traverse(from, context)))
			return (ret);
		if ((ptr = ptr->next))
			ptr = ptr->next;
	}
	return (SUCCESS);
}

int				sh_traverse_pipe_sequence(t_ast_node *node, t_context *context)
{
	int		ret;

	ret = SUCCESS;
	sh_traverse_tools_show_traverse_start(node, context);
	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		ret = sh_traverse_pipe_sequences_redirections(node, context);
	else if (context->phase == E_TRAVERSE_PHASE_EXECUTE)
		ret = sh_traverse_pipe_sequence_execute(node, context);
	else
		ret = sh_traverse_tools_browse(node, context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
