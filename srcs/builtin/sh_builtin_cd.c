/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 17:43:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/30 14:07:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_cd(t_context *context)
{
	char	*param;
	char	*curpath;
	char	flags;
	int		i;
	int		ret;

	i = 1;
	curpath = NULL;
	if ((ret = sh_builtin_cd_parser(context, &i, &flags, &curpath)))
		return (ret);
	param = argv[index];
	if (!param)
		param = curpath;
	ft_dprintf(2, "curpath (post parse): %s\n", curpath);
	if ((ret = sh_builtin_cd_pre_rules(context, param, &curpath)))
		return (ret);
	ft_dprintf(2, "curpath (post pre): %s\n", curpath);
	if (!args[CD_P_OPT].value)
	{
		sh_builtin_cd_rule7(context, &curpath, args);
		ft_dprintf(2, "curpath (rule 7): %s\n", curpath);
		sh_builtin_cd_rule8_1(&curpath);
	}
	ft_dprintf(2, "curpath (past 7 and 8): %s\n", curpath);
	index = sh_builtin_cd_rule10(context, curpath, args, param);
	free(curpath);
	return (ret);
}
