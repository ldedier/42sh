/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_parser_usage.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 04:49:29 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 04:54:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_parser_show:
**	Used for debugging.
*/

void		sh_builtin_parser_show(t_args args[])
{
	while (args && args->type != E_ARGS_END)
	{
		if (args->type == E_ARGS_BOOL)
		{
			ft_dprintf(2,
			"short : %c || long : %s || value : %p || priority : %d\n",
			args->name_short, args->name_long, args->value, args->priority);
		}
		else if (args->type == E_ARGS_INT)
		{
			ft_dprintf(2,
			"short : %c || long : %s || value : %d || priority : %d\n",
			args->name_short, args->name_long, args->value, args->priority);
		}
		else if (args->type == E_ARGS_STRING)
		{
			ft_dprintf(2,
			"short : %c || long : %s || value : %s || priority : %d\n",
			args->name_short, args->name_long, args->value, args->priority);
		}
		args++;
	}
}

int			sh_builtin_usage(
	t_args ag[], char *name, char *usage, t_context *context)
{
	int		i;
	int		fd;

	fd = FD_ERR;
	isatty(2) ? ft_dprintf(fd, SH_ERR_COLOR) : 0;
	ft_dprintf(fd, "Usage: %s %s\n", name, usage);
	i = 0;
	while (ag && ag[i].type != E_ARGS_END)
	{
		if (ag[i].name_short && ag[i].name_long)
			ft_dprintf(fd, "  -%c, --%s", ag[i].name_short, ag[i].name_long);
		else if (ag[i].name_short)
			ft_dprintf(fd, "  -%c", ag[i].name_short);
		else if (ag[i].name_long)
			ft_dprintf(fd, "  --%s", ag[i].name_long);
		if (ag[i].usage)
			ft_dprintf(fd, ": %s", ag[i].usage);
		if (ag[i].name_short || ag[i].name_long || ag[i].usage)
			ft_dprintf(fd, "\n");
		i++;
	}
	isatty(2) ? ft_dprintf(fd, EOC) : 0;
	sh_env_update_ret_value(context->shell, SH_RET_ARG_ERROR);
	return (ERROR);
}
