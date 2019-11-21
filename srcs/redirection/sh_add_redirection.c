/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:41:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 20:24:25 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_redirection(
	t_redirection redirection, t_list **list, int is_builtin)
{
	if (sh_execute_redirection(&redirection, is_builtin) != SUCCESS)
		return (STOP_CMD_LINE);
	if (ft_lstaddnew(list, &redirection, sizeof(t_redirection)))
	{
		sh_perror(SH_ERR1_MALLOC, "sh_add_redirection");
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** If it already exist and the redirect fd (right fd) was closed, we have to
** re-close it.
*/

static int	sh_add_redirection(
	t_redirection redirection, t_list **list, int is_builtin)
{
	if (redirection.fd >= 0
		&& sh_check_dst_fd(*list, redirection.fd) == -1)
	{
		ft_dprintf(2, "%s%s: %d: bad file descriptor\n%s", SH_ERR_COLOR,
		SH_NAME, redirection.fd, EOC);
		return (ERROR);
	}
	else if (sh_check_src_fd(*list, &redirection) == -1)
	{
		sh_perror(SH_ERR1_INTERN_ERR, "Error to apply redirection");
		return (STOP_CMD_LINE);
	}
	if (redirection.was_closed == -1)
		redirection.was_closed = 0;
	return (sh_process_redirection(redirection, list, is_builtin));
}

int			sh_add_redirection_file(
	t_redirection_type type, t_context *context, int fd)
{
	t_redirection	redirection;

	redirection = sh_new_redir(type, context->redirected_fd, fd);
	redirection.was_closed = 1;
	return (sh_add_redirection(
				redirection, &context->redirections, context->is_builtin));
}

int			sh_add_redirection_aggreg(
	t_redirection_type type, t_context *context, int fd)
{
	t_redirection	redirection;

	if (context->redirected_fd == fd)
		return (SUCCESS);
	redirection = sh_new_redir(type, context->redirected_fd, fd);
	return (sh_add_redirection(
				redirection, &context->redirections, context->is_builtin));
}

int			sh_add_redirection_pipe(int fd, t_list **list)
{
	t_redirection	redirection;

	redirection = sh_new_redir(PIPE, -1, fd);
	redirection.was_closed = 1;
	if (ft_lstaddnew(list, &redirection, sizeof(t_redirection)))
	{
		sh_perror(SH_ERR1_MALLOC, "sh_add_redirection");
		return (ERROR);
	}
	return (SUCCESS);
}
