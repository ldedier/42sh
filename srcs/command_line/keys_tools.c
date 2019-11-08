/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:44:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 20:44:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		await_stream(int fd)
{
	fd_set			set;
	struct timeval	timeout;
	int				ret;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	ret = select(1, &set, NULL, NULL, &timeout);
	if (ret == 1)
		return (1);
	else
		return (0);
}
