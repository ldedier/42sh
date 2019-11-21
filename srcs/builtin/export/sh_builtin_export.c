/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 09:45:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/13 05:20:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** assign_assignment:
**	Used in the case taht argument is a key=value like, where value can be null.
**	If the key is found in vars table it is transfered to saved_env,
**	else it is only created / updated in saved_env table.
**
**	Returnd Values:
**		SUCCESS
**		FAILURE : malloc error
*/

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

/*
** assign_empty_variable:
**	Fonction used if argument is a key, with no '=' char.
**	It first looks in vars and env tables, if any assignments correspond
**	to that key, this assignment is transfered from current table to saved_env.
**	Else, if key do not exist in saved_env it is created.
**
**	Returnd Values:
**		SUCCESS
**		FAILURE : malloc error
*/

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

static void	sh_builtin_export_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'p', NULL, NULL, EXPORT_P_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

int			sh_builtin_export(t_context *context)
{
	char	**argv;
	int		index;
	t_args	args[2];
	int		buf;
	int		ret;

	sh_builtin_export_init_args(args);
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
