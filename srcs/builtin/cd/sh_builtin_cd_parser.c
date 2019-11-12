/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 03:21:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/11 03:47:45 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_parser_hyphen:
**	Set curpath to OLDPWD env value, if it exists.
**	Change argument in context->param : "-" => old pwd value.
**
**	Returned Values :
**		SUCCESS : param successfully replaced by oldpwd
**		ERROR : OLDPWD not set in env
**		FAILURE : malloc error
*/

static int	sh_builtin_cd_parser_hyphen(
	t_context *context, t_args *args, char **curpath, int i)
{
	char	*oldpwd;

	if (!(oldpwd = sh_vars_get_value(context->env, NULL, "OLDPWD")))
	{
		sh_perror_err(SH_ERR1_ENV_NOT_SET, "OLDPWD");
		return (ERROR);
	}
	free(context->params->tbl[i]);
	if (!(context->params->tbl[i] = ft_strdup(oldpwd)))
	{
		ft_strdel(curpath);
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_parser_hyphen"));
	}
	args[CD_HYPHEN_OPT].value = args;
	return (SUCCESS);
}

/*
** sh_builtin_cd_parser:
**	Read options given to cd, using sh_builtin_parser functions.
**	It also handle the hyphen option. As said in posix specifications :
**	`cd -` shall be equivalent to `cd "$OLDPWD" && pwd`
**	If none of -P and -L options is not given, then -L is set as default value.
**
**	Returned Values :
**		SUCCESS : Parsed options and modified params if in HYPHEN case
**		ERROR : Error in options given, OLDPWD not set in env
**		FAILURE : malloc error in hyphen treatment
*/

int			sh_builtin_cd_parser(t_context *context, t_args *args,
	int *index, char **curpath)
{
	int		ret;
	char	**argv;

	argv = (char**)context->params->tbl;
	*curpath = NULL;
	if (sh_builtin_parser(ft_strtab_len(argv), argv, args, index))
		return (sh_builtin_usage(args, argv[0], CD_USAGE, context));
	if (argv[*index] && argv[*index + 1])
		return (sh_perror_err(argv[0], SH_ERR1_TOO_MANY_ARGS));
	if (ft_strequ(argv[*index], "-"))
	{
		if ((ret = sh_builtin_cd_parser_hyphen(context, args, curpath, *index)))
			return (ret);
	}
	if (!args[CD_P_OPT].value && !args[CD_L_OPT].value)
	{
		args[CD_L_OPT].value = &args;
		args[CD_L_OPT].priority++;
	}
	return (SUCCESS);
}
