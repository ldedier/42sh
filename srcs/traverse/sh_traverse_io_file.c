/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_io_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:19:41 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 18:24:05 by mdaoud           ###   ########.fr       */
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
		return (sh_add_redirection_file(OUTPUT, context, -1));
	else if ((fd = get_fd(filename)) >= 0)
		return (sh_add_redirection_aggreg(OUTPUT, context, fd));
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
		return (sh_add_redirection_file(INPUT, context, -1));
	else if ((fd = get_fd(filename)) >= 0)
		return (sh_add_redirection_aggreg(INPUT, context, fd));
	else
	{
		if (fd == -1)
			return (sh_perror_err(filename, SH_AMB_REDIRECT));
		else
		{
			ft_dprintf(2, "%s%s: %s : %d%s\n", SH_ERR_COLOR,
				SH_NAME, SH_ERR1_BAD_FD, fd, COLOR_END);
		}
		return (ERROR);
	}
}

/*
** get_io_file_return
** dispatch to right function follow
** input/output with file/agregation redirection
*/

static int	get_io_file_return(t_ast_node *redir_child,
			char *filename, t_context *context)
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

/*
** sh_traverse_io_file
** We get here file and aggregation redirection and
** add the given id or the created file fd to the list
** of redirection we will run.
*/

long		sh_traverse_io_file(t_ast_node *node, t_context *context)
{
	t_ast_node	*redir_child;
	t_ast_node	*filename_child;
	char		*filename;
	int			ret;

	redir_child = node->children->content;
	filename_child = node->children->next->content;
	filename_child = filename_child->children->content;
	filename = filename_child->token->value;
	ret = SUCCESS;
	if (context->phase == E_TRAVERSE_PHASE_EXPANSIONS)
	{
		filename = ft_strdup(filename);
		if ((ret = sh_expansions(context, filename_child)) == SUCCESS
					&& (filename_child->parent->children->next
						|| !filename_child->token->value[0]))
			ret = sh_perror_err(SH_AMB_REDIRECT, filename);
		free(filename);
	}
	else if (context->phase == E_TRAVERSE_PHASE_REDIRECTIONS)
		if ((ret = get_io_file_return(redir_child, filename, context)))
			sh_env_update_ret_value(context->shell, ret);
	return (ret);
}
