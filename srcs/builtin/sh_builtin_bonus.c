/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:43:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/25 07:23:19 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#if __APPLE__ && __MACH__

int		sh_builtin_🐑(t_context *context)
{
	(void)context;
	if (write(FD_OUT, NULL, 0))
	{
		return (sh_perror2_err("write error", "export", SH_ERR1_BAD_FD));
	}
	ft_dprintf(FD_OUT, "behhhh\n");
	return (SUCCESS);
}

#endif
