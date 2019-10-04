/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 09:45:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/04 03:15:01 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	assign_assignment(t_context *context, char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	*equal = 0;
	if (sh_env_save_get_index(context->vars, arg))
		sh_vars_del_key(context->vars, arg);
	*equal = '=';
	if (sh_vars_assignment(context->saved_env, NULL, arg))
		return (sh_perror(SH_ERR1_MALLOC, "export : assign_assignment"));
	if (ft_strnstr(arg, "PATH", 4))
		sh_builtin_hash_empty_table(context->shell);
	return (SUCCESS);
}

static int	assign_empty_variable(t_context *context, char *arg)
{
	int		index;

	if ((index = sh_env_save_get_index(context->vars, arg)) >= 0)
	{
		if (sh_vars_assignment(
			context->saved_env, NULL, context->vars->tbl[index]))
			return (sh_perror(SH_ERR1_MALLOC, "export : assign_empty (0)"));
		ft_dy_tab_suppr_index(context->vars, index);
	}
	else if ((index = sh_env_save_get_index(context->env, arg)) >= 0)
	{
		if (sh_vars_assignment(
			context->saved_env, NULL, context->env->tbl[index]))
			return (sh_perror(SH_ERR1_MALLOC, "export : assign_empty (1)"));
		ft_dy_tab_suppr_index(context->env, index);
	}
	else if ((index = sh_env_save_get_index(context->saved_env, arg)) == -1)
	{
		if (ft_dy_tab_add_str(context->saved_env, arg))
			return (sh_perror(SH_ERR1_MALLOC, "export : assign_empty (2)"));
	}
	return (SUCCESS);
}

static int	sh_builtin_export_assign(t_context *context, char *arg)
{
	if (!sh_expansions_variable_valid_name(arg))
		return (sh_perror2_err(arg, "export", "not a valid identifier"));
	if (ft_strchr(arg, '='))
	{
		if (assign_assignment(context, arg))
			return (FAILURE);
	}
	else
	{
		if (assign_empty_variable(context, arg))
			return (FAILURE);
	}
	return (SUCCESS);
}

int			sh_builtin_export(t_context *context)
{
	char	**argv;
	int		index;
	t_args	args[] = {
		{E_ARGS_BOOL, 'p', NULL, NULL, EXPORT_P_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};
	int		buf;
	int		ret;

	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], EXPORT_USAGE, context));
	if (!argv[index])
		return (sh_builtin_export_show(context));
	ret = SUCCESS;
	while (argv[index])
	{
		if ((buf = sh_builtin_export_assign(context, argv[index])) == FAILURE)
			return (FAILURE);
		index++;
		if (buf)
			ret = ERROR;
	}
	return (ret);
}
