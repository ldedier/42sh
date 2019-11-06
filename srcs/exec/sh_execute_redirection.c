/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:52:43 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/04 11:26:48 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int	sh_execute_redirection(t_redirection *el)
{
	if (sh_verbose_pipe())
		ft_dprintf(2, "Redirections %d:\n", el->fd);
	if (el->fd >= 0)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\t%d became %d\n",
					el->fd, el->redirected_fd);
		if (dup2(el->fd, el->redirected_fd) == -1)
			return (sh_perror(SH_ERR1_INTERN_ERR,
						"executing redirection"));
	}
	else if (el->fd == -1)
	{
		if (sh_verbose_pipe())
			ft_dprintf(2, "\tclosing %d\n", el->redirected_fd);
		close(el->redirected_fd);
	}
	return (SUCCESS);
}
