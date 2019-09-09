/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/09 11:53:20 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	get_fd(char *filename)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (filename[i])
	{
		if (!ft_isdigit(filename[i]))
			return (-1);
		res = res * 10 + filename[i] - '0';
		i++;
	}
	return (res);
}

static int	sh_process_file_greatand(char *filename, t_context *context)
{
	int fd;

	if (!ft_strcmp(filename, "-"))
	{
		if (sh_add_redirection(OUTPUT, context->redirected_fd, -1,
		&context->current_command_node->metadata.command_metadata.redirections))
			return (FAILURE);
		return (SUCCESS);
	}
	else if ((fd = get_fd(filename)) >= 0)
	{
		return (sh_add_fd_aggregation(OUTPUT, context->redirected_fd, fd,
			&context->current_command_node->
				metadata.command_metadata));
	}
	if (fd == -1)
		return (sh_process_file_output(filename, context, GREAT_OPT));
	ft_dprintf(2, "%s%s: %s : %d%s\n", SH_ERR_COLOR,
		SH_NAME, SH_ERR1_BAD_FD, fd, COLOR_END);
	return (SUCCESS);
}

static int	sh_process_file_lessand(char *filename, t_context *context)
{
	int fd;

	if (!ft_strcmp(filename, "-"))
	{
		if (sh_add_redirection(INPUT, context->redirected_fd, -1,
			&context->current_command_node->
				metadata.command_metadata.redirections))
			return (FAILURE);
		return (SUCCESS);
	}
	else if ((fd = get_fd(filename)) >= 0)
		return (sh_add_fd_aggregation(INPUT, context->redirected_fd, fd,
			&context->current_command_node->
				metadata.command_metadata));
	else
	{
		if (fd == -1)
			return (sh_perror_err(filename, "ambiguous redirect"));
		else
		{
			ft_dprintf(2, "%s%s: %s : %d%s\n", SH_ERR_COLOR,
				SH_NAME, SH_ERR1_BAD_FD, fd, COLOR_END);
		}
		return (ERROR);
	}
}

static int			get_io_file_return(t_ast_node *redir_child,
			char *filename, t_context *context)
{
	if (context->current_command_node->metadata.command_metadata.should_exec)
	{
		if (redir_child->symbol->id == sh_index(LEX_TOK_LESS))
			return (sh_process_file_input(filename, context, O_RDONLY));
		else if (redir_child->symbol->id == sh_index(LEX_TOK_DGREAT)
				|| redir_child->symbol->id == sh_index(LEX_TOK_CLOBBER))
			return (sh_process_file_output(filename, context, DGREAT_OPT));
		else if (redir_child->symbol->id == sh_index(LEX_TOK_GREAT))
			return (sh_process_file_output(filename, context, GREAT_OPT));
		else if (redir_child->symbol->id == sh_index(LEX_TOK_GREATAND))
			return (sh_process_file_greatand(filename, context));
		else if (redir_child->symbol->id == sh_index(LEX_TOK_LESSAND))
			return (sh_process_file_lessand(filename, context));
		else
			return (SUCCESS);
	}
	else
		return (SUCCESS);
}

int			sh_traverse_io_file(t_ast_node *node, t_context *context)
{
	t_ast_node	*redir_child;
	t_ast_node	*filename_child;
	char		*filename;
	int			ret;

	if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
	{
		redir_child = node->children->content;
		filename_child = node->children->next->content;
		filename = ((t_ast_node *)
			(filename_child->children->content))->token->value;
		ret = get_io_file_return(redir_child, filename, context);
		if (ret)
			sh_env_update_ret_value(context->shell, ret);
		return (ret);
	}
	return (sh_traverse_tools_browse(node, context));
}
