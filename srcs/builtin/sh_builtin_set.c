/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/25 07:24:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


static void		print_builtin_usage(void)
{
	sh_perror("set [-o option] [+o option]\n", NULL);
}

int				print_options_minus(t_shell *shell)
{
	(void)shell;
	if (g_glob.command_line.edit_style == E_EDIT_STYLE_VIM)
		ft_printf("vim\t\ton\n");
	else
		ft_printf("vim\t\toff\n");
	return (SUCCESS);
}

int				print_options_plus(t_shell *shell)
{
	(void)shell;
	ft_printf("set ");
	if (g_glob.command_line.edit_style == E_EDIT_STYLE_VIM)
		ft_printf("+o vim\n");
	else
		ft_printf("-o vim\n");
	return (SUCCESS);
}

int			fill_option_value(int **address_ptr, int *value_ptr,
				int *address, int value)
{
	*address_ptr = address;
	*value_ptr = value;
	return (1);
}

int			get_option(t_shell *shell, char *option_name,
				int  **option, int *value)
{
	(void)shell;
	if (!ft_strcmp(option_name, "vi"))
	{
		return (fill_option_value(option, value,
		((int*)&g_glob.command_line.edit_style), E_EDIT_STYLE_VIM));
	}
	return (0);
}

int			add_option(t_context *context, int index)
{
	int		*opt;
	int		value;
	char	*option_name;

	option_name = (char *)context->params->tbl[index];
	if (get_option(context->shell, option_name, &opt, &value))
		*opt = value;
	else
	{
		ft_dprintf(2, "%s%s%s", SH_ERR_COLOR, "set: unknown option", EOC);
	}
	return (SUCCESS);
}
int			remove_option(t_context *context, int index)
{
	int		*opt;
	int		value;
	char	*option_name;

	option_name = (char *)context->params->tbl[index];
	if (get_option(context->shell, option_name, &opt, &value))
		*opt = !value;
	else
	{
		ft_dprintf(2, "%s%s", SH_ERR_COLOR, "set: unknown option", EOC);
	}
	return (SUCCESS);
}

int		sh_builtin_set_param(t_context *context, int *index)
{
	if (!ft_strcmp(context->params->tbl[*index], "-o"))
	{
		(*index)++;
		if (*index == (int)context->params->current_size)
			return (print_options_minus(context->shell));
		else
			return (add_option(context, (*index)++));
	}
	else if (!ft_strcmp(context->params->tbl[*index], "+o"))
	{
		(*index)++;
		if (*index == (int)context->params->current_size)
			return (print_options_plus(context->shell));
		else
			return (remove_option(context, (*index)++));
	}
	else
	{
		print_builtin_usage();
		return (ERROR);
	}
}

int			sh_builtin_set_args(t_context *context)
{
	int i;

	i = 1;
	while (i < (int)context->params->current_size)
	{
		sh_builtin_set_param(context, &i);
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_set_print_all(t_context *context)
{
	int i;

	i = 0;
	while (context->env->tbl[i])
	{
		ft_putstr_fd(context->env->tbl[i], FD_OUT);
		ft_putchar_fd('\n', FD_OUT);
		i++;
	}
	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	i = 0;
	while (context->vars->tbl[i])
	{
		if (!(*(char*)(context->vars->tbl[i]) == '?'
					|| *(char*)(context->vars->tbl[i]) == '$'
					|| *(char*)(context->vars->tbl[i]) == '#'))
		{
			ft_putstr_fd(context->vars->tbl[i], FD_OUT);
			ft_putchar_fd('\n', FD_OUT);
		}
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_set(t_context *context)
{
	int		i;

	i = 0;
	if (context->params->current_size == 1)
		return (sh_builtin_set_print_all(context));
	else
		return (sh_builtin_set_args(context));
	return (SUCCESS);
}
