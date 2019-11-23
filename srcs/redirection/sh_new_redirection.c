/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_new_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:35:05 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 13:36:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_redirection	sh_new_redir(
	t_redirection_type type, int redirected_fd, int fd)
{
	t_redirection redir;

	redir.type = type;
	redir.backup = -1;
	redir.fd = fd;
	redir.was_closed = -1;
	if (redirected_fd == -1 && type != PIPE)
	{
		if (type == INPUT)
			redir.redirected_fd = STDIN_FILENO;
		else if (type == OUTPUT)
			redir.redirected_fd = STDOUT_FILENO;
	}
	else
		redir.redirected_fd = redirected_fd;
	return (redir);
}
