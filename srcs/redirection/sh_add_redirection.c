/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_add_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:41:47 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/09 10:41:49 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
 * Check if the fd to redirect (left fd) already exist for the same type (I/O)
 * to overwrite the destination fd (right fd) and not multiply redirection.
 *
 * Return t_redirection * on the existing element redirection
 * Otherwise return NULL
*/
static t_redirection	*is_redirection_already_exist(t_redirection_type type,
					int redirected_fd, t_list *list)
{
	t_list			*ptr;
	t_redirection	*redirection;

	ptr = list;
	while (ptr != NULL)
	{
		redirection = ptr->content;
		if (redirection->type == type
				&& redirection->redirected_fd == redirected_fd)
			return (redirection);
		ptr = ptr->next;
	}
	return (NULL);
}

static t_redirection		sh_new_redir(
	t_redirection_type type, int redirected_fd, int fd)
{
	t_redirection redir;

	redir.type = type;
	// redir.closed = 0;
	redir.fd = fd;
	redir.was_apply = 0;
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

/*
 * Create and add redirection in the redirection list
 * We check if the redirection already exist
 * before create a new one.
 * The redirection is considerate aleardy existing if the redirected_fd (left)
 * and the type (input or output) are the same.
 *
 * If it already exist and the redirect fd (right fd) was closed, we have to
 * re-close it.
*/
int				sh_add_redirection(t_redirection_type type, int redirected_fd,
			int fd, t_list **list)
{
	t_redirection	*found;
	t_redirection	redirection;

	redirection = sh_new_redir(type, redirected_fd, fd);
	if (!(found = is_redirection_already_exist(redirection.type,
		redirection.redirected_fd, *list)))
	{
		if (ft_lstaddnew_last(list, &redirection, sizeof(t_redirection)))
		{
			sh_perror(SH_ERR1_MALLOC, "sh_add_redirection");
			return (ERROR);
		}
	}
	else
	{
		if (found->fd > 2)
			close(found->fd);
		found->fd = redirection.fd;
	}
	return (SUCCESS);
}