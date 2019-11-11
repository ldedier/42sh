/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_pre_rules.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:50:45 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/12 00:13:55 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_pre_rules:
**	1. If no directory operand is given and the HOME environment variable is
**	empty or  undefined,  the  default  behavior  is  implementation-defined.
**	2. If  no  directory operand is given and the HOME environment variable is
**	set to a non-empty value, the cd utility shall behave as if the directory
**	named in the HOME environment variable was specified as the operand.
**	3. If the directory operand begins with a <slash> character, set curpath to
**	the operand and proceed to step 7.
**	4. If the first component of the directory operand is dot or dot-dot,
**	proceed to step 6.
**	5 : use CDPATH (see sh_builtin_cd_rule5)
**	6 : Set curpath to directory operand (Applied in sh_builtin_cd_rule5).
**
**	Returned Values
**		SUCCESS : Filled *curpath
**		ERROR : Home not set
**		FAILURE : malloc error
*/

int			sh_builtin_cd_pre_rules(
	t_context *context, char *param, char **curpath, t_args *args)
{
	char	*home;

	home = sh_vars_get_value(context->env, NULL, "HOME");
	if ((!param) && (!home || !*home))
		return (sh_perror_err(SH_ERR1_ENV_NOT_SET, "HOME"));
	else if (!param)
		*curpath = ft_strdup(home);
	else if (*param == '/')
		*curpath = ft_strdup(param);
	else if (*param == '.' || ft_strnstr(param, "..", 2))
		*curpath = ft_strdup(param);
	else
		return (sh_builtin_cd_rule5(context, curpath, param, args));
	if (!*curpath)
	{
		sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_pre_rules");
		return (FAILURE);
	}
	return (SUCCESS);
}
