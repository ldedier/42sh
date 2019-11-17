/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:55:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:56:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_builtin_set_print_assignment(char *assignment)
{
	int		i;

	if (!ft_strpbrk(assignment, " \n\t\"\\\'$"))
	{
		ft_putstrn(assignment);
		return ;
	}
	i = ft_strchr(assignment, '=') - assignment;
	assignment[i] = '\0';
	ft_putstr(assignment);
	ft_putstr("=\"");
	assignment[i] = '=';
	i++;
	while (assignment[i])
	{
		if (ft_strchr("\"\'\\$", assignment[i]))
			ft_putchar('\\');
		ft_putchar(assignment[i]);
		i++;
	}
	ft_putstr("\"\n");
}

static void	sh_builtin_set_print_vars(t_context *context)
{
	int i;

	i = 0;
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"set : vars table :\n"EOC);
	while (context->vars->tbl[i])
	{
		if (!(*(char*)(context->vars->tbl[i]) == '?'
					|| *(char*)(context->vars->tbl[i]) == '$'
					|| *(char*)(context->vars->tbl[i]) == '#'))
			sh_builtin_set_print_assignment(context->vars->tbl[i]);
		i++;
	}
}

int			sh_builtin_set_print(t_context *context)
{
	int i;

	i = 0;
	if (write(FD_OUT, NULL, 0))
	{
		return (sh_perror2_err("write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	}
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"set : saved_env table :\n"EOC);
	while (context->saved_env->tbl[i])
	{
		if (ft_strchr(context->saved_env->tbl[i], '='))
			sh_builtin_set_print_assignment(context->saved_env->tbl[i]);
		i++;
	}
	sh_builtin_set_print_vars(context);
	return (SUCCESS);
}
