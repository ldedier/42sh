/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_verbose_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:48:59 by jmartel           #+#    #+#             */
/*   Updated: 2019/07/02 21:49:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_verbose_ast(void)
{
	if (g_glob.verbose & VERBOSE_AST)
		return (1);
	return (0);
}

int		sh_verbose_lexer(void)
{
	if (g_glob.verbose & VERBOSE_LEXER)
		return (1);
	return (0);
}

int		sh_verbose_exec(void)
{
	if (g_glob.verbose & VERBOSE_EXEC)
		return (1);
	return (0);
}

int		sh_verbose_pipe(void)
{
	if (g_glob.verbose & VERBOSE_PIPE)
		return (1);
	return (0);
}

int		sh_verbose_expansion(void)
{
	if (g_glob.verbose & VERBOSE_EXPANSION)
		return (1);
	return (0);
}

int		sh_verbose_builtin(void)
{
	if (g_glob.verbose & VERBOSE_BUILTIN)
		return (1);
	return (0);
}

int		sh_verbose_traverse(void)
{
	if (g_glob.verbose & VERBOSE_TRAVERSE)
		return (1);
	return (0);
}
