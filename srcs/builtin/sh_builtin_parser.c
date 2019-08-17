/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:19:47 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/17 22:34:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	parser_get_arg_content(t_args *args, char **argv, int *index)
{
	args->priority = *index;
	if (args->type == E_ARGS_BOOL)
		args->value = &args;
	else if (args->type == E_ARGS_STRING || args->type == E_ARGS_INT)
	{
		if (!argv[*index + 1] || argv[*index + 1][0] == '-')
			return (FAILURE);
		args->value = argv[*index + 1];
		index += 1;
		return (SUCCESS);
	}
	else if (args->type == E_ARGS_INT)
	{
		if (!argv[*index + 1] || argv[*index + 1][0] == '-')
			return (FAILURE);
		args->value = argv[*index + 1];
		*index += 1;
		return (SUCCESS);
		
	}
	return (SUCCESS);
}

static int	paser_long_arg(char **argv, int *index, t_args args[])
{
	int		i;

	i = 0;
	while (args[i].type != E_ARGS_END)
	{
		if (ft_strequ(args[i].name_long, argv[*index] + 2))
			return (parser_get_arg_content(args + i, argv, index));
		i++;
	}
	return (FAILURE);
}

static int	paser_short_arg(char **argv, int *index, t_args args[])
{
	int		i;
	int		j;

	i = 0;
	while (args[i].type != E_ARGS_END)
	{
		j = 1;
		while (argv[*index][j])
		{
			if (args[i].name_short == argv[*index][j])
				return (parser_get_arg_content(args + i, argv, index));
			j++;
		}
		i++;
	}
	return (FAILURE);
}

int		sh_builtin_usage(t_args args[], char *name, char *usage)
{
	int		i;

	ft_dprintf(2, SH_ERR_COLOR);
	ft_dprintf(2, "Usage: %s %s\n", name, usage);
	i = 0;
	while (args && args[i].type != E_ARGS_END)
	{
		if (args[i].name_short && args[i].name_short)
			ft_dprintf(2, "  -%c, --%s", args[i].name_short, args[i].name_long);
		else if (args[i].name_short)
			ft_dprintf(2, "  -%c", args[i].name_short);
		else if (args[i].name_long)
			ft_dprintf(2, "  --%s", args[i].name_short, args[i].name_long);
		if (args[i].usage)
			ft_dprintf(2, ": %s", usage);
		ft_dprintf(2, "\n");
		i++;
	}
	ft_dprintf(2, EOC);
	return (FAILURE);
}

int		sh_builtin_parser_is_boolean(t_args args[], char opt)
{
	while (args->type != E_ARGS_END)
	{
		if (args->name_short == opt)
		{
			if (args->value)
				return (1);
			return (0);
		}
		args++;
	}
	return (0);
}

int		sh_builtin_parser(int argc, char **argv, t_args args[], int *index)
{
	int		ret;

	*index = 1;
	ret = 0;
	// ft_dprintf(2, "builtin parser : argc = %d\nargv : \n", argc);
	// ft_strtab_put(argv);
	// ft_dprintf(2, "(null)\n");

	while (*index < argc && argv[*index] && !ret)
	{
		if (argv[*index][0] == '-' && argv[*index][1] == '-')
		{
			if (argv[*index][2] == '\0')
			{
				(*index)++;
				return (SUCCESS);
			}
			ret = paser_long_arg(argv, index, args);
		}
		else if (argv[*index][0] == '-' && argv[*index][1] != '\0')
			ret = paser_short_arg(argv, index, args);
		else
			break ;
		(*index)++;
	}
	return (ret);
}

void	sh_builtin_parser_show(t_args args[])
{
	while (args && args->type != E_ARGS_END)
	{
		if (args->type == E_ARGS_BOOL)
			ft_dprintf(2, "short : %c || long : %s || value : %p || priority : %d\n", args->name_short, args->name_long, args->value, args->priority);
		else if (args->type == E_ARGS_INT)
			ft_dprintf(2, "short : %c || long : %s || value : %d || priority : %d\n", args->name_short, args->name_long, args->value, args->priority);
		else if (args->type == E_ARGS_STRING)
			ft_dprintf(2, "short : %c || long : %s || value : %s || priority : %d\n", args->name_short, args->name_long, args->value, args->priority);
		args++;
	}
}
