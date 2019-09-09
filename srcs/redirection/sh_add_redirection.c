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

static t_redirection	*get_redirection(t_redirection_type type,
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

static t_redirection	sh_new_redir(t_redirection_type type, int redirected_fd, int fd)
{
	t_redirection redir;

	redir.type = type;
	redir.closed = 0;
	redir.redirected_fd = redirected_fd;
	redir.fd = fd;
	return (redir);
}

int				sh_add_redirection(t_redirection_type type, int redirected_fd,
			int fd, t_list **list)
{
	t_redirection	*found;
	t_redirection	redirection;

	redirection = sh_new_redir(type, redirected_fd, fd);
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