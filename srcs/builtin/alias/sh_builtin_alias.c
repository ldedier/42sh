/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_alias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:45:49 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/15 14:41:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	sh_builtin_alias_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'p', NULL, NULL, ALIAS_P_OPT_USAGE, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

int			alias_valid_name(char *str)
{
	int		i;
	char	*start;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] == '_' || ft_isalnum(str[i]) || str[i] == '!'
			|| str[i] == '%' || str[i] == ','
			|| str[i] == '@' || str[i] == '.'))
			return (0);
		i++;
	}
	if ((start = ft_strstr(str, "$("))
		&& sh_expansions_cmd_subst_detect_dollar(start) != -1)
		return (-1);
	if ((start = ft_strchr(str, '`'))
		&& sh_expansions_cmd_subst_detect_backquotes(start) != -1)
		return (-1);
	if ((start = ft_strstr(str, "<("))
		&& sh_expansions_proc_subst_out_detect(start) != -1)
		return (-1);
	if ((start = ft_strstr(str, ">("))
		&& sh_expansions_proc_subst_in_detect(start) != -1)
		return (-1);
	return (1);
}

static int	alias_treat_argument(t_context *context, char *arg)
{
	int		index;

	if (!arg || arg[0] == '=')
		return (sh_perror2_err(arg, "alias", "not found"));
	if (!ft_strchr(arg, '='))
	{
		if ((index = sh_vars_get_index(context->alias, arg)) != -1)
			show_alias(((char**)context->alias->tbl)[index]);
		else
			return (sh_perror2_err(arg, "alias", "not found"));
	}
	else
	{
		if (!(index = alias_valid_name(arg)))
			return (sh_perror2_err(arg, "alias", "invalid alias name"));
		if (index == -1)
			return (sh_perror2_err(arg, "alias", "cannot alias substitutions"));
		if (sh_vars_assignment(context->alias, NULL, arg))
			return (FAILURE);
		if (sh_verbose_builtin())
			ft_dprintf(2, MAGENTA"alias : created alias : %s\n"EOC, arg);
	}
	return (SUCCESS);
}

/*
** sh_builtin_alias:
**	As bash does, we do not check for write errors on stdout.
*/

int			sh_builtin_alias(t_context *context)
{
	char	**argv;
	int		index;
	t_args	args[2];
	int		buf;
	int		ret;

	sh_builtin_alias_init_args(args);
	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], ALIAS_USAGE, context));
	if (!argv[index])
		return (sh_builtin_alias_show(context));
	ret = SUCCESS;
	while (argv[index])
	{
		if ((buf = alias_treat_argument(context, argv[index])) == FAILURE)
			return (FAILURE);
		index++;
		if (buf)
			ret = ERROR;
	}
	return (ret);
}
