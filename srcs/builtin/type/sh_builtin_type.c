/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/12 06:59:36 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_type_show_not_found:
**	If options require it, print error message for a not found parameter.
**
**	Returned Values
**		ERROR
*/

static int	sh_builtin_type_show_not_found(char *arg, t_args *args)
{
	if (!args[TYPE_T_OPT].value && !args[TYPE_P_OPT].value)
		ft_dprintf(FD_ERR, "%s: type: %s: not found\n", SH_NAME, arg);
	return (ERROR);
}

/*
** sh_builtin_type_efault:
**	For every argument look in aliases, reserved words, builtins,
**	hash table and in path.
**	If any argument do not have any match, error is returned when every
**	parameters had been treated.
**	Error message is shown only if any flag from -p and -t are specified.
**
**	Returned Values
**		SUCCESS : Found at least on match for every argument
**		ERROR : At least on argument had no match
**		FAILURE : malloc error when searching in path
*/

static int	sh_builtin_type_default(
	t_context *context, t_args args[], int i, char **argv)
{
	int		ret;
	int		buffer;

	ret = SUCCESS;
	while (argv[i++])
	{
		if (!sh_builtin_type_search_alias(argv[i - 1], args, context))
			continue ;
		if (!sh_builtin_type_search_reserved(argv[i - 1], args))
			continue ;
		if (!sh_builtin_type_search_builtin(argv[i - 1], args))
			continue ;
		if (!sh_builtin_type_search_hash(context, argv[i - 1], args))
			continue ;
		if (((buffer = sh_builtin_type_search_in_path(
				context, argv[i - 1], args)) == FAILURE))
			return (FAILURE);
		if (!buffer)
			continue ;
		ret = sh_builtin_type_show_not_found(argv[i - 1], args);
	}
	return (ret);
}

/*
** sh_builtin_type_all:
**	For every argument look in aliases, reserved words, builtins and in path.
**	It does not look in hash table.
**	When looking in path it show every binary matching argument.
**	If any argument do not have any match, error is returned when every
**	parameters had been treated.
**	Error message is shown only if any flag from -p and -t are specified.
**
**	Returned Values
**		SUCCESS : Found at least on match for every argument
**		ERROR : At least on argument had no match
**		FAILURE : malloc error when searching in path
*/

static int	sh_builtin_type_all(
	t_context *context, t_args args[], int i, char **argv)
{
	int		ret;
	int		found;
	int		buffer;

	ret = SUCCESS;
	while (argv[i++])
	{
		found = 0;
		found += !sh_builtin_type_search_alias(argv[i - 1], args, context);
		found += !sh_builtin_type_search_reserved(argv[i - 1], args);
		found += !sh_builtin_type_search_builtin(argv[i - 1], args);
		buffer = sh_builtin_type_search_in_path(context, argv[i - 1], args);
		if (buffer == FAILURE)
			return (FAILURE);
		found += !buffer;
		if (found)
			continue ;
		ret = sh_builtin_type_show_not_found(argv[i - 1], args);
	}
	return (ret);
}

/*
** sh_builtin_type_init_args:
**	Initialize t_args table used in type.
*/

static void	sh_builtin_type_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'a', NULL, NULL, TYPE_A_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'p', NULL, NULL, TYPE_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 't', NULL, NULL, TYPE_T_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

/*
** sh_builtin_type:
**	After parsing alias options, it choose between two different procedure :
**	default, and all (if '-a' is given).
**
**	Returned Values
**		SUCCESS
**		ERROR : At least one argmument do not matched anything, write error
**		FAILURE : malloc error
*/

int			sh_builtin_type(t_context *context)
{
	int				index;
	char			**argv;
	t_args			args[4];

	sh_builtin_type_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], TYPE_USAGE, context));
	if (argv[index] && write(FD_OUT, NULL, 0))
	{
		return (sh_perror2_err("write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	}
	if (args[TYPE_A_OPT].value)
		return (sh_builtin_type_all(context, args, index, argv));
	return (sh_builtin_type_default(context, args, index, argv));
}
