/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/30 15:03:42 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_cd(t_context *context)
{
	char	*curpath;
	int		index;
	char	**argv;
	char	*param;
	t_args	args[] = {
		{E_ARGS_BOOL, 'P', NULL, NULL, CD_P_OPT_USAGE, 0},
		{E_ARGS_BOOL, 'L', NULL, NULL, CD_L_OPT_USAGE, 0},
		{E_ARGS_BOOL, 0, NULL, NULL, NULL, 0},
		{E_ARGS_END, 0, NULL, NULL, NULL, 0},
	};
	int		ret;

	argv = (char**)context->params->tbl;
	if ((ret = sh_builtin_cd_parser(context, args, &index, &curpath, argv)))
		return (ret);
	param = argv[index];
	if (!param)
		param = curpath;
	if ((ret = sh_builtin_cd_pre_rules(context, param, &curpath)))
		return (ret);
	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		sh_builtin_cd_rule7(context, &curpath, args);
		sh_builtin_cd_rule8_1(&curpath);
	}
	index = sh_builtin_cd_rule10(context, curpath, args, param);
	if (curpath)
		free(curpath);
	return (index);
}
