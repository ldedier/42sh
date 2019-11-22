/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_open_fd_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:42:32 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 13:43:22 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			is_open(int fd)
{
	struct stat buf;

	if (fstat(fd, &buf) == -1)
		return (0);
	else
		return (1);
}

/*
** sh_check_open_fd
** We need to check if the the right fd is a valid open fd.
** We use fcntl function cause testing with write on a pipe
** could break the shell. This was used to appened with this specific command :
** cmd > fifo | echo 2
*/

int			sh_check_open_fd(int fd)
{
	if (fcntl(fd, F_GETFL) != -1)
		return (fd);
	return (-1);
}
