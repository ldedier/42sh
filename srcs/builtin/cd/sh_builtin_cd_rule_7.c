/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_cd_rule_7.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 02:58:10 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/12 00:19:25 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_builtin_cd_rule7:
**	Only if in logical mode. (Else execute rule 10)
**	If curpath is a relative path (do not start with '/'), set curpath to
**	concatenation of current working directory and curpath. A '/' is added
**	between them if needed.
**
**	Returned Values:
**		ERROR : Can't get current working directory (sh_builtin_pwd)
**		SUCCESS : Can continue process
*/

int			sh_builtin_cd_rule7(
	t_context *context, char **curpath, t_args *args)
{
	char	*pwd;

	if (args[CD_L_OPT].priority > args[CD_P_OPT].priority)
	{
		if (**curpath != '/')
		{
			if (!(pwd = sh_builtin_pwd_logical(context->env)))
			{
				free(*curpath);
				return (ERROR);
			}
			if (!(*curpath = ft_strjoin_path_free(pwd, *curpath, 0x01 + 0x02)))
				return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_cd_rule7"));
		}
	}
	if (sh_verbose_builtin())
		ft_dprintf(2, MAGENTA"cd : after 7 : curpath = %s\n"EOC, *curpath);
	return (SUCCESS);
}
