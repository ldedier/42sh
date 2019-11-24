/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 20:38:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 20:38:12 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	buf;
	int		ret;

	if (argc > 1)
		fd = atoi(argv[1]);
	else
		fd = 1;
	while ((ret = read(fd, &buf, 1)))
	{
		if (ret == -1)
		{
			dprintf(1, "Read error\n");
			return (1);
		}
		dprintf(1, "%c", buf);
	}
	return (0);
}
