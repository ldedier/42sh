/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:13:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/04 21:50:40 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_builtin_type_all(
	t_context *context, t_args args[], int index, char **argv)
{
	int		ret;
	int		found;
	int		buffer;

	ret = SUCCESS;
	while (argv[index])
	{
		index++;
		found = 0;
		found += !sh_builtin_type_search_reserved(
			context, argv[index - 1], args);
		found += !sh_builtin_type_search_builtin(
			context, argv[index - 1], args);
		buffer = sh_builtin_type_search_in_path(context, argv[index - 1], args);
		if (buffer == FAILURE)
			return (FAILURE);
		found += !buffer;
		if (found)
			continue ;
		if (!args[TYPE_T_OPT].value && !args[TYPE_P_OPT].value)
		{
			ft_dprintf(context->fd[FD_ERR],
			"%s: type: %s: not found\n", SH_NAME, argv[index - 1]);
		}
		ret = ERROR;
	}
	return (ret);
}

int			sh_builtin_type(t_context *context)
{
	int				index;
	char			**argv;
	int				ret;
	int				buffer;
	t_args			args[] = {
		{E_ARGS_BOOL, 'a', NULL, NULL, TYPE_A_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'p', NULL, NULL, TYPE_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 't', NULL, NULL, TYPE_T_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], TYPE_USAGE, context));
	if (argv[index] && write(context->fd[FD_OUT], NULL, 0))
	{
		return (sh_perror2_err_fd(context->fd[FD_ERR], "write error",
			context->params->tbl[0], SH_ERR1_BAD_FD));
	}
	if (args[TYPE_A_OPT].value)
		return (sh_builtin_type_all(context, args, index, argv));
	ret = SUCCESS;
	while (argv[index])
	{
		index++;
		if (!sh_builtin_type_search_reserved(context, argv[index - 1], args))
			continue ;
		if (!sh_builtin_type_search_builtin(context, argv[index - 1], args))
			continue ;
		if (!sh_builtin_type_search_hash(context, argv[index - 1], args))
			continue ;
		if (((buffer = sh_builtin_type_search_in_path(
				context, argv[index - 1], args)) == FAILURE))
			return (buffer);
		if (!buffer)
			continue ;
		if (!args[TYPE_T_OPT].value && !args[TYPE_P_OPT].value)
		{
			ft_dprintf(context->fd[FD_ERR], "%s: type: %s: not found\n",
				SH_NAME, argv[index - 1]);
		}
		ret = ERROR;
	}
	return (ret);
}
