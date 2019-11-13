/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:19:47 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 04:49:42 by jmartel          ###   ########.fr       */
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
			return (ERROR);
		args->value = argv[*index + 1];
		index += 1;
		return (SUCCESS);
	}
	else if (args->type == E_ARGS_INT)
	{
		if (!argv[*index + 1] || argv[*index + 1][0] == '-')
			return (ERROR);
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
		if (ft_strequ("help", argv[*index] + 2))
			return (ERROR);
		i++;
	}
	return (ERROR);
}

static int	paser_short_arg(char **argv, int *index, t_args args[])
{
	int		i;
	int		j;
	int		found;

	i = 1;
	while (argv[*index][i])
	{
		found = 0;
		j = 0;
		while (args[j].type != E_ARGS_END)
		{
			if (args[j].name_short == argv[*index][i])
			{
				if (parser_get_arg_content(args + j, argv, index))
					return (ERROR);
				i++;
				found = 1;
				break ;
			}
			j++;
		}
		if (found)
			continue ;
		ft_memmove(argv[*index] + 1, argv[*index] + i, 1);
		argv[*index][2] = 0;
		return (sh_perror2_err(argv[*index], argv[0], "invalid option"));
	}
	return (SUCCESS);
}

int			sh_builtin_parser(int argc, char **argv, t_args args[], int *index)
{
	int		ret;

	*index = 1;
	ret = 0;
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
