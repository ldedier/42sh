/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_verbose.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:19:57 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/29 05:09:20 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

#define VERBOSE_USAGE			"[-lapextb] [--option] [on/off]"
#define VERBOSE_L_OPT			0
#define VERBOSE_A_OPT			1
#define VERBOSE_P_OPT			2
#define VERBOSE_E_OPT			3
#define VERBOSE_X_OPT			4
#define VERBOSE_T_OPT			5
#define VERBOSE_B_OPT			6
#define VERBOSE_ALL_OPT			7

static int	sh_builtin_verbose_process(
	t_context *context, t_args args[], char *state)
{
	int			i;
	char		value[3];
	const char	key[9][20] = {"verbose_lexer", "verbose_ast", "verbose_pipe",
		"verbose_exec", "verbose_expansion", "verbose_traverse",
		"verbose_builtin", ""};

	i = 0;
	if (ft_strequ(state, "on"))
		ft_strcpy(value, "on");
	else
		ft_strcpy(value, "");
	while (args[i].type != E_ARGS_END)
	{
		if (args[i].value || args[VERBOSE_ALL_OPT].value)
			if (sh_vars_assign_key_val(
					NULL, context->vars, (char*)key[i], value))
				return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int			sh_builtin_verbose(t_context *context)
{
	int				index;
	char			**argv;
	t_args			args[] = {
		{E_ARGS_BOOL, 'l', "lexer", NULL, NULL, 0},
		{E_ARGS_BOOL, 'a', "ast", NULL, NULL, 0},
		{E_ARGS_BOOL, 'p', "pipe", NULL, NULL, 0},
		{E_ARGS_BOOL, 'e', "exec", NULL, NULL, 0},
		{E_ARGS_BOOL, 'x', "expansion", NULL, NULL, 0},
		{E_ARGS_BOOL, 't', "traverse", NULL, NULL, 0},
		{E_ARGS_BOOL, 'b', "builtin", NULL, NULL, 0},
		{E_ARGS_BOOL, '\0', "all", NULL, "Every options activated", 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	argv = (char**)context->params->tbl;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, &index))
		return (sh_builtin_usage(args, argv[0], VERBOSE_USAGE, context));
	if (index == 1 || (argv[index] && argv[index + 1]))
		return (sh_builtin_usage(args, argv[0], VERBOSE_USAGE, context));
	if (!argv[index] || ft_strequ(argv[index], "on"))
		return (sh_builtin_verbose_process(context, args, "on"));
	else if (ft_strequ(argv[index], "off"))
		return (sh_builtin_verbose_process(context, args, "off"));
	else
		return (sh_builtin_usage(args, argv[0], VERBOSE_USAGE, context));
}
