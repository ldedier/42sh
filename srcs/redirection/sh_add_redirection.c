/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:41:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/23 16:40:31 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_redirection	sh_new_redir(
	t_redirection_type type, int redirected_fd, int fd)
{
	t_redirection redir;

	redir.type = type;
	redir.backup = -1;
	redir.fd = fd;
	redir.was_closed = -1;
	if (redirected_fd == -1)
	{
		if (type == INPUT)
			redir.redirected_fd = STDIN_FILENO;
		else
			redir.redirected_fd = STDOUT_FILENO;
	}
	else
		redir.redirected_fd = redirected_fd;
	return (redir);
}

static int			sh_process_redirection(
	t_redirection redirection, t_list **list)
{

	if (sh_execute_redirection(*list, &redirection) != SUCCESS)
		return (STOP_CMD_LINE);
	if (ft_lstaddnew(list, &redirection, sizeof(t_redirection)))
	{
		sh_perror(SH_ERR1_MALLOC, "sh_add_redirection");
		return (ERROR);
	}
	return (SUCCESS);
}

/*
 * If it already exist and the redirect fd (right fd) was closed, we have to
 * re-close it.
*/
// static int			sh_add_redirection(
// 	t_redirection_type type, int redirected_fd, int fd, t_list **list)
static int			sh_add_redirection(
	t_redirection redirection, /*int redirected_fd, int fd,*/ t_list **list)
{
	// t_redirection	redirection;

	// redirection = sh_new_redir(type, redirected_fd, fd);
	if (redirection.fd >= 0
		&& sh_check_dst_fd(*list, redirection.type, redirection.fd) == -1)
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
	return (sh_process_redirection(redirection, list));
}

int 				sh_add_redirection_file(
	t_redirection_type type, int redirected_fd, int fd, t_list **list)
{
	t_redirection	redirection;

	redirection = sh_new_redir(type, redirected_fd, fd);
	redirection.was_closed = 1;
	return (sh_add_redirection(redirection, list));
}

int					sh_add_redirection_aggreg(
	t_redirection_type type, int redirected_fd, int fd, t_list **list)
{
	t_redirection	redirection;

	if (redirected_fd == fd)
		return (SUCCESS);
	redirection = sh_new_redir(type, redirected_fd, fd);
	return (sh_add_redirection(redirection, list));
}
