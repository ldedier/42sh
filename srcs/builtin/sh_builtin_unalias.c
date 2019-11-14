/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unalias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 23:15:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 05:16:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define UNALIAS_USAGE			"alias-name... || unalias -a"
#define UNALIAS_A_OPT			0
#define UNALIAS_A_OPT_USAGE		"remove all alias definitions for current shell"

static void	sh_builtin_unalias_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'a', NULL, NULL, UNALIAS_A_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

static int	sh_builtin_unalias_process(
	t_context *context, char **argv, int index)
{
	int		ret;

	ret = SUCCESS;
	while (argv[index])
	{
		if (!alias_valid_name(argv[index]) || ft_strrchr(argv[index], '='))
			ret = sh_perror2_err(argv[index], "unalias", "not found");
		else if (sh_vars_get_index(context->alias, argv[index]) == -1)
			ret = sh_perror2_err(argv[index], "unalias", "not found");
		else
			sh_vars_del_key(context->alias, argv[index]);
		index++;
	}
	return (ret);
}

int			sh_builtin_unalias(t_context *context)
{
	char	**argv;
	int		index;
	t_args	args[2];

	sh_builtin_unalias_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], UNALIAS_USAGE, context));
	if (args[UNALIAS_A_OPT].value)
	{
		ft_dy_tab_empty(context->alias);
		return (SUCCESS);
	}
	else if (!argv[index])
		return (sh_builtin_usage(args, argv[0], UNALIAS_USAGE, context));
	return (sh_builtin_unalias_process(context, argv, index));
}
