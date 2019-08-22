/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:43:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/22 18:36:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#if __APPLE__ && __MACH__

int		sh_builtin_🐑(t_context *context)
{
	if (write(context->fd[FD_OUT], NULL, 0))
		return (sh_perror2_err_fd(context->fd[FD_ERR], "write error",
			"export", SH_ERR1_BAD_FD));
	ft_dprintf(context->fd[FD_OUT], "behhhh\n");
	return (SUCCESS);
}

#endif
