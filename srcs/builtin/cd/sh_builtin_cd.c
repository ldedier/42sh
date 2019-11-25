/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 23:10:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_body:
**	Here is decomposition of posix rules : pre_rules is implementing
**	rules 1 to 4, and rule 6. They try to set curpath using different
**	informations.
**
**	Returned Values :
**		SUCCESS : Successfuly changed directory
**		ERROR : File is invalid for some reasons, write error
**		FAILURE : malloc error
*/

static int	sh_builtin_cd_body(
	t_context *context, t_args *args, int index, char **curpath)
{
	int		ret;
	char	*param;

	param = ((char**)context->params->tbl)[index];
	if ((ret = sh_builtin_cd_pre_rules(context, param, curpath, args)))
		return (ret);
	if (!param)
		param = *curpath;
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : rules 1 - 6 : curpath = %s\n"EOC, *curpath);
	if (*curpath && **curpath)
		ret = sh_builtin_cd_check_perms(*curpath, param);
	else if (param && *param)
		ret = sh_builtin_cd_check_perms(param, param);
	if (!ret && args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		sh_builtin_cd_rule7(context, curpath, args);
		ret = sh_builtin_cd_rule8(curpath);
	}
	if (!ret)
		ret = sh_builtin_cd_rule10(context, *curpath, args, param);
	ft_strdel(curpath);
	return (ret);
}

/*
** sh_builtin_cd_init_args:
**	Initialize t_args table used in cd.
*/

static void	sh_builtin_cd_init_args(t_args *args)
{
	const t_args model[] = {
		{E_ARGS_BOOL, 'P', NULL, NULL, CD_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'L', NULL, NULL, CD_L_OPT_USAGE, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	ft_memcpy(args, model, sizeof(model));
}

/*
** sh_builtin_cd:
**	The cd builtin shall change the working directory of the current shell.
**	PWD and OLDPWD are updated. See posix procedure that I followed on :
**	https://www.unix.com/man-page/posix/1posix/cd/
**	This function is declaring variables that will be used in all
**	subfunctions : curpath, index, args. It also init args table, and call
**	parsing function.
**	Third unamed option is used as a boolean to store if we are an hyphen case:
**	`cd -`, to show current path at the end of the function.
**
** returned Values :
**		ERROR
**		FAILURE : malloc error
**		SUCCESS
*/

int			sh_builtin_cd(t_context *context)
{
	char	*curpath;
	int		index;
	int		ret;
	t_args	args[4];

	sh_builtin_cd_init_args(args);
	if ((ret = sh_builtin_cd_parser(context, args, &index, &curpath)))
		return (ret);
	return (sh_builtin_cd_body(context, args, index, &curpath));
}
