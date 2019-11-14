/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:19:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 04:39:16 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define UNSET_USAGE			"[-fv] name..."
#define UNSET_V_OPT			0
#define UNSET_V_OPT_USAGE	"unset variables (default option)"
#define UNSET_F_OPT			1
#define UNSET_F_OPT_USAGE	"unset fuctions"

static void	unset_variable(t_context *context, char **argv, int index)
{
	int		i;

	if (sh_vars_get_index(context->vars, argv[index]) >= 0)
	{
		if (sh_verbose_builtin())
			ft_dprintf(2, MAGENTA"unset : found %s in vars\n"EOC, argv[index]);
		sh_vars_del_key(context->vars, argv[index]);
	}
	else if ((i = sh_env_save_get_index(context->saved_env, argv[index])) >= 0)
	{
		if (sh_verbose_builtin())
			ft_dprintf(
				2, MAGENTA"unset : found %s in saved_env\n"EOC, argv[index]);
		ft_dy_tab_suppr_index(context->saved_env, i);
	}
	else
	{
		if (sh_verbose_builtin())
			ft_dprintf(2, MAGENTA"unset : cannot find %s !!\n"EOC, argv[index]);
	}
	if (ft_strnstr(argv[index], "PATH", 4))
		sh_builtin_hash_empty_table(context->shell);
}

static void	sh_builtin_unset_init_args(t_args *args)
{
	const t_args	model[] = {
		{E_ARGS_BOOL, 'v', NULL, NULL, UNSET_V_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'f', NULL, NULL, UNSET_F_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

int			sh_builtin_unset(t_context *context)
{
	char	**argv;
	int		index;
	int		ret;
	t_args	args[3];

	sh_builtin_unset_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], UNSET_USAGE, context));
	if (args[UNSET_F_OPT].priority > args[UNSET_V_OPT].priority)
		return (SUCCESS);
	ret = SUCCESS;
	while (argv[index])
	{
		if (!sh_expansions_variable_valid_name(argv[index])
				|| ft_strchr(argv[index], '='))
			ret = sh_perror2_err(
				argv[index], "unset", "not a valid identifier");
		else
			unset_variable(context, argv, index);
		index++;
	}
	return (ret);
}
