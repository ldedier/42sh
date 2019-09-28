/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:19:24 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/28 23:24:49 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define UNSET_USAGE			"[-fv] name..."
#define UNSET_V_OPT			0
#define UNSET_V_OPT_USAGE	"unset variables (default option)"
#define UNSET_F_OPT			1
#define UNSET_F_OPT_USAGE	"unset fuctions"

static int	sh_builtin_unset_get_index(char **tbl, char *arg)
{
	int		i;

	i = 0;
	while (tbl[i])
	{
		if (ft_strequ(tbl[i], arg))
			return (i);
		i++;
	}
	return (-1);
}

int			sh_builtin_unset(t_context *context)
{
	char	**argv;
	int		index;
	t_args	args[] = {
		{E_ARGS_BOOL, 'v', NULL, NULL, UNSET_V_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'f', NULL, NULL, UNSET_F_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};
	int		ret;
	int		i;

	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], UNSET_USAGE, context));
	if (args[UNSET_F_OPT].priority > args[UNSET_V_OPT].priority)
		return (SUCCESS);
	ret = SUCCESS;
	while (argv[index])
	{
		if (!sh_expansions_variable_valid_name(argv[index]) || ft_strchr(argv[index], '='))
			ret = sh_perror2_err(argv[index], "unset", "not a valid identifier");
		if (sh_vars_get_index(context->vars, argv[index]) >= 0)
		{
			if (sh_verbose_builtin())
				ft_dprintf(2, "unset : found %s in vars\n", argv[index]);
			sh_vars_del_key(context->vars, argv[index]);
		}
		else if (sh_vars_get_index(context->saved_env, argv[index]) >= 0)
		{
			if (sh_verbose_builtin())
				ft_dprintf(2, "unset : found %s in saved_env\n", argv[index]);
			sh_vars_del_key(context->saved_env, argv[index]);
		}
		else if ((i = sh_builtin_unset_get_index((char**)context->saved_env->tbl, argv[index])) >= 0)
		{
			if (sh_verbose_builtin())
				ft_dprintf(2, "unset : found %s in saved_env\n", argv[index]);
			ft_dy_tab_suppr_index(context->saved_env, i);
		}
		if (ft_strnstr(argv[index], "PATH", 4))
			sh_builtin_hash_empty_table(context->shell);
		index++;
	}
	return (ret);
}
