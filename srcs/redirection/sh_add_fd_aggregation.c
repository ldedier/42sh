/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:16:56 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/09 11:00:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** returns the destination fd (right), (-1 if closed) or
** -2 if the fd specified is not open
*/

static int				get_redirected_fd(t_redirection_type type,
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

int				sh_add_fd_aggregation(t_redirection_type type,
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
			return (sh_add_redirection(type, redirected_fd, new_fd,
						&metadata->redirections));
	}
	else
		return (SUCCESS);
}
