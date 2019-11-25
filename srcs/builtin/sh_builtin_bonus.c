/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 15:43:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/25 11:27:00 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_bonus(t_context *context)
{
	char		**argv;

	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error", "export", SH_ERR1_BAD_FD));
	argv = (char**)context->params->tbl;
	if (!argv[1])
		ft_dprintf(1, "🐑\n");
	else if (argv[2])
		ft_dprintf(1, "💥\n");
	else if (ft_strequ(argv[1], "beeeh"))
		ft_dprintf(1, "🥚\n");
	else if (ft_strequ(argv[1], "hot"))
		ft_dprintf(1, "🌮\n");
	else
		ft_dprintf(1, "💥\n");
	return (SUCCESS);
}
