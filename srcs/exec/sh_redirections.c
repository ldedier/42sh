/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:16:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/02 16:34:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_redirection	*get_redirection(t_redirection_type type,
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

int				sh_add_redirection(t_redirection redirection, t_list **list)
{
	t_redirection	*found;

	if (redirection.redirected_fd == -1)
	{
		if (redirection.type == INPUT)
			redirection.redirected_fd = 0;
		else
			redirection.redirected_fd = 1;
	}
	if (!(found = get_redirection(redirection.type,
		redirection.redirected_fd, *list)))
	{
		if (ft_lstaddnew_last(list, &redirection, sizeof(t_redirection)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_add_redirection"));
	}
	else
	{
		if (found->fd > 2)
			close(found->fd);
		found->fd = redirection.fd;
	}
	return (SUCCESS);
}

/*
** returns the redirected fd, (-1 if closed) or
** -2 if the fd specified is not open
*/

int				get_redirected_fd(t_redirection_type type,
					int fd, t_list *redirections)
{
	t_list			*ptr;
	t_redirection	*redir;

	ptr = redirections;
	while (ptr != NULL)
	{
		redir = (t_redirection *)ptr->content;
		if (redir->type == type && redir->redirected_fd == fd)
			return (redir->fd);
		ptr = ptr->next;
	}
	if (fd >= 0 && fd <= 2)
		return (fd);
	else
		return (-2);
}

int				sh_process_fd_aggregation(t_redirection_type type,
					int redirected_fd, int fd, t_command_metadata *metadata)
{
	int new_fd;

	if (fd != redirected_fd)
	{
		if ((new_fd = get_redirected_fd(type, fd, metadata->redirections))
			== -2)
		{
			ft_dprintf(2, "%s%s: %d: bad file descriptor\n%s", SH_ERR_COLOR,
			SH_NAME, fd, EOC);
			metadata->should_exec = 0;
			return (SUCCESS);
		}
		else
			return (sh_add_redirection(sh_new_redir(
				type, redirected_fd, new_fd), &metadata->redirections));
	}
	else
		return (SUCCESS);
}

t_redirection	sh_new_redir(t_redirection_type type, int redirected_fd, int fd)
{
	t_redirection redir;

	redir.type = type;
	redir.closed = 0;
	redir.redirected_fd = redirected_fd;
	redir.fd = fd;
	return (redir);
}
