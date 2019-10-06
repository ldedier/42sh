/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/05 04:16:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
		ft_dprintf(2, MAGENTA"cd : after prerules : curpath = %s\n"EOC, *curpath);
	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		sh_builtin_cd_rule7(context, curpath, args);
		sh_builtin_cd_rule8(curpath);
	}
	index = sh_builtin_cd_rule10(context, *curpath, args, param);
	if (*curpath)
		free(*curpath);
	return (index);
}

/*
** sh_builtin_cd:
**	The cd builtin shall change the working directory of the current shell.
**	PWD and OLDPWD are updated. See posix procedure that I followed on :
**	https://www.unix.com/man-page/posix/1posix/cd/
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
	t_args	args[] = {
		{E_ARGS_BOOL, 'P', NULL, NULL, CD_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'L', NULL, NULL, CD_L_OPT_USAGE, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};

	if ((ret = sh_builtin_cd_parser(context, args, &index, &curpath)))
		return (ret);
	return (sh_builtin_cd_body(context, args, index, &curpath));
}
