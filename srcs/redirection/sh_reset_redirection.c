/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_reset_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:05:17 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 13:37:56 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	reset_input_output_redirection(t_redirection *el)
{
	if (el->backup >= 0)
	{
		if (dup2(el->backup, el->redirected_fd) < 0)
			return (sh_perror(SH_ERR1_INTERN_ERR, "can't reset redirections"));
		close(el->backup);
	}
	else
		close(el->redirected_fd);
	if (el->was_closed && el->fd >= 0)
		close(el->fd);
	return (SUCCESS);
}

int			sh_reset_redirection(t_list **lst)
{
	t_redirection	*el;
	t_list			*del;
	int				ret;

	while (*lst)
	{
		el = (*lst)->content;
		if (el->type == PIPE)
			close(el->fd);
		else if ((ret = reset_input_output_redirection(el) != SUCCESS))
			return (ret);
		del = *lst;
		(*lst) = (*lst)->next;
		free(el);
		free(del);
	}
	return (SUCCESS);
}
