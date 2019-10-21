/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:00:32 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/08 15:17:39 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"


static void		print_builtin_usage(void)
{
	sh_perror("set [-o option] [+o option]", NULL);
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
		ft_dprintf(2, "%s%s%s", SH_ERR_COLOR, "set: unknown option\n", EOC);
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
		ft_dprintf(2, "%s%s", SH_ERR_COLOR, "set: unknown option\n", EOC);
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
			return (add_option(context, *index));
	}
	else if (!ft_strcmp(context->params->tbl[*index], "+o"))
	{
		(*index)++;
		if (*index == (int)context->params->current_size)
			return (print_options_plus(context->shell));
		else
			return (remove_option(context, *index));
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
	int ret;

	i = 1;
	while (i < (int)context->params->current_size)
	{
		if ((ret = sh_builtin_set_param(context, &i)))
			return (ret);
		i++;
	}
	return (SUCCESS);
}

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

static int	sh_builtin_set_print(t_context *context)
{
	int i;

	i = 0;
	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"set : saved_env table :\n"EOC);
	while (context->saved_env->tbl[i])
	{
		if (ft_strchr(context->saved_env->tbl[i], '='))
			sh_builtin_set_print_assignment(context->saved_env->tbl[i]);
		i++;
	}
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
	return (SUCCESS);
}

int			sh_builtin_set(t_context *context)
{
	if (context->params->current_size == 1)
		return (sh_builtin_set_print(context));
	else
		return (sh_builtin_set_args(context));
	return (SUCCESS);
}
