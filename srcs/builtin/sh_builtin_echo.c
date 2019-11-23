/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:57:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/17 15:08:15 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_echo_write(char *str)
{
	int		len;
	int		ret;

	if ((len = ft_strlen(str)) == 0)
		return (SUCCESS);
	ret = write(FD_OUT, str, len);
	if (ret == -1)
	{
		return (sh_perror2_err("echo", "write error", SH_ERR1_BAD_FD));
	}
	return (SUCCESS);
}

int			sh_builtin_echo(t_context *context)
{
	int		i;
	int		ret;

	if (!context->params->tbl[1])
		return (sh_builtin_echo_write("\n"));
	i = 1;
	while (context->params->tbl[i] && ft_strequ(context->params->tbl[i], "-n"))
		i++;
	ret = 0;
	while (!ret && context->params->tbl[i] && context->params->tbl[i + 1])
	{
		ret = sh_builtin_echo_write(context->params->tbl[i]);
		if (!ret)
			ret = sh_builtin_echo_write(" ");
		i++;
	}
	if (ret)
		return (ERROR);
	if (sh_builtin_echo_write(context->params->tbl[i]) == ERROR)
		return (ERROR);
	if (!ft_strequ(context->params->tbl[1], "-n"))
		return (sh_builtin_echo_write("\n"));
	return (SUCCESS);
}
