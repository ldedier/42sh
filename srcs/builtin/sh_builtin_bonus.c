/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:43:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/21 11:59:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#if __APPLE__ && __MACH__

int		sh_builtin_🐑(t_context *context)
{
	ft_dprintf(context->fd[FD_OUT], "behhhh\n");
	return (SUCCESS);
}

#endif
