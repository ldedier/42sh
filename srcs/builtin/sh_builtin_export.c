/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 09:45:53 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/29 01:35:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define EXPORT_MSG			"declare -x" // need to be changed to "export"
#define EXPORT_USAGE		"name[=word]"
#define EXPORT_P_OPT		0
#define EXPORT_P_OPT_USAGE	"print all exported variables (default option)"

static int	sh_builtin_export_show_min(char **min, char **env)
{
	int		i;
	char	*new_min;

	if (!min || !*min) // look for first minimal value
	{
		*min = env[0];
		i = 1;
		while (env[i])
		{
			if (ft_strcmp(*min, env[i]) > 0)
				*min = env[i];
			i++;
		}
		return (SUCCESS);
	}
	else
	{
		i = 0;
		new_min = NULL;
		while (env[i])
		{
			if (!new_min)
			{
				if (ft_strcmp(*min, env[i]) < 0)
					new_min =  env[i];
			}
			else if (ft_strcmp(new_min, env[i]) > 0 && ft_strcmp(*min, env[i]) < 0)
				new_min = env[i];
			i++;
		}
		*min = new_min;
	}
	return (SUCCESS);
}

static int	sh_builtin_export_show(t_context *context)
{
	char	**tbl;
	char	*min;
	char	*equal;
	int		i;

	if (write(FD_OUT, NULL, 0))
		return (sh_perror2_err("write error", "export", SH_ERR1_BAD_FD));
	tbl = (char**)(context->saved_env->tbl);
	min = NULL;
	sh_builtin_export_show_min(&min, tbl);
	while (min)
	{
		if (!(equal = ft_strchr(min, '=')))
			ft_printf("%s %s\n", EXPORT_MSG, min);
		else
		{
			*equal = '\0';
			ft_printf("%s %s=", EXPORT_MSG, min);
			i = 1;
			ft_putchar('\"');
			while (equal[i])
			{
				if (equal[i] == '\'' || equal[i] == '\\' || equal[i] == '\"')
					ft_putchar('\\');
				ft_putchar(equal[i]);
				i++;
			}
			ft_putchar('\"');
			ft_putchar('\n');
			*equal = '=';
		}
		sh_builtin_export_show_min(&min, tbl);
	}
	return (SUCCESS);
}

static int	sh_builtin_export_get_index(t_dy_tab *vars, char *key)
{
	int		i;
	int		j;
	char	**tbl;

	i = 0;
	tbl = (char**)vars->tbl;
	while (tbl[i])
	{
		j = 0;
		while (tbl[i][j] && key[j] && tbl[i][j] == key[j])
			j++;
		if (key[j] == 0 && (tbl[i][j] == '=' || tbl[i][j] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static int		sh_builtin_export_assign(t_context *context, char *arg)
{
	char	*equal;
	int		index;

	if (!sh_expansions_variable_valid_name(arg))
		return (sh_perror2_err(arg, "export", "not a valid identifier"));
	if ((equal = ft_strchr(arg, '=')))
	{
		*equal = 0;
		if (sh_builtin_export_get_index(context->vars, arg))
			sh_vars_del_key(context->vars, arg);
		*equal = '=';
		if (sh_vars_assignment(context->saved_env, NULL, arg))
			return (FAILURE); // perror
		if (ft_strnstr(arg, "PATH", 4))
			sh_builtin_hash_empty_table(context->shell);
	}
	else
	{
		if ((index = sh_builtin_export_get_index(context->vars, arg)) >= 0)
		{
			if (sh_vars_assignment(context->saved_env, NULL, context->vars->tbl[index]))
				return (FAILURE); // perror
			ft_dy_tab_suppr_index(context->vars, index);
			;//transfer vars -> env;
		}
		else if ((index = sh_builtin_export_get_index(context->saved_env, arg)) == -1)
		{
			if (ft_dy_tab_add_str(context->saved_env, arg))
				return (FAILURE); // perror
		}
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
