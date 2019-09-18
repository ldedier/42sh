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

int				sh_add_fd_aggregation(t_redirection_type type,
					int redirected_fd, int fd, t_list **redirections)
{
	int new_fd;

	if (fd != redirected_fd)
	{
		// if ((new_fd = get_redirected_fd(type, fd)) == -1)
		if ((new_fd = sh_check_open_fd(type, fd)) == -1)
		{
			ft_dprintf(2, "%s%s: %d: bad file descriptor\n%s", SH_ERR_COLOR,
			SH_NAME, fd, EOC);
			return (STOP_CMD_LINE);
		}
		else
			return (sh_add_redirection(type, redirected_fd, new_fd,
						redirections));
	}
	else
		return (SUCCESS);
}
