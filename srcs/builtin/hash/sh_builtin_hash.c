/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:18:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/13 05:21:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define HASH_USAGE			"[-r] [utility...]"
#define HASH_R_OPT			0
#define HASH_R_OPT_USAGE	"Forget all previously remembered utility locations"

static int	sh_builtin_hash_process_utilities(t_context *context, int i)
{
	int				ret;
	t_hash_finder	finder;

	while (context->params->tbl[i])
	{
		ret = sh_builtin_hash_add_utility(context, context->params->tbl[i]);
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == ERROR)
			sh_env_update_ret_value(context->shell, ret);
		else
		{
			finder = ft_hash_table_find(context->shell->binaries,
				context->params->tbl[i], ft_hash_str, compare_str_to_binary);
			if (finder.found)
				((t_binary*)finder.current->content)->hits = 0;
		}
		i++;
	}
	return (SUCCESS);
}

static void	sh_builtin_hash_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'r', NULL, NULL, HASH_R_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

int			sh_builtin_hash(t_context *context)
{
	int		index;
	char	**argv;
	t_args	args[2];

	sh_builtin_hash_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], HASH_USAGE, context));
	if (!args[HASH_R_OPT].value && !argv[index])
		return (sh_builtin_hash_show(context->shell));
	if (args[HASH_R_OPT].value)
		sh_builtin_hash_empty_table(context->shell);
	return (sh_builtin_hash_process_utilities(context, index));
}
