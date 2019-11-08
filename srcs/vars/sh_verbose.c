/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verbose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:16:38 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/16 01:07:56 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_verbose_update_check:
**	Check for if var designed by str exists and is not empty. If true verbose
**	mode is enabled for phase designed by param.
**	Else it is unabled.
*/

static void	sh_verbose_update_check(t_shell *shell, int param, char *str)
{
	char	*value;

	if ((value = sh_vars_get_value(shell->env, shell->vars,
		str)) && *value)
		g_glob.verbose += g_glob.verbose & param ? 0 : param;
	else
		g_glob.verbose -= g_glob.verbose & param ? param : 0;
}

/*
** sh_verbose_update:
**	Update the g_glob.verbose var detecting for special
**	variables in shell->vars.
*/

void		sh_verbose_update(t_shell *shell)
{
	sh_verbose_update_check(shell, VERBOSE_AST, "verbose_ast");
	sh_verbose_update_check(shell, VERBOSE_LEXER, "verbose_lexer");
	sh_verbose_update_check(shell, VERBOSE_EXEC, "verbose_exec");
	sh_verbose_update_check(shell, VERBOSE_BUILTIN, "verbose_builtin");
	sh_verbose_update_check(shell, VERBOSE_EXPANSION, "verbose_expansion");
	sh_verbose_update_check(shell, VERBOSE_PIPE, "verbose_pipe");
	sh_verbose_update_check(shell, VERBOSE_TRAVERSE, "verbose_traverse");
	sh_verbose_update_check(shell, VERBOSE_GLOBBING, "verbose_globbing");
}

/*
**	Check if verbose is active on in the given phase.
**
** Returned Values:
**		True or False
*/

int			sh_verbose_traverse(void)
{
	if (g_glob.verbose & VERBOSE_TRAVERSE)
		return (1);
	return (0);
}

/*
**	Check if verbose is active on in the given phase.
**
** Returned Values:
**		True or False
*/

int			sh_verbose_builtin(void)
{
	if (g_glob.verbose & VERBOSE_BUILTIN)
		return (1);
	return (0);
}

/*
**	Check if verbose is active on in the given phase.
**
** Returned Values:
**		True or False
*/

int			sh_verbose_globbing(void)
{
	if (g_glob.verbose & VERBOSE_GLOBBING)
		return (1);
	return (0);
}
