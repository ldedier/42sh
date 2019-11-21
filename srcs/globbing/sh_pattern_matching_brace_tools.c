/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_brace_tools.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:24:22 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:25:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_pattern_matching_brace_dash_not(
	char *name, t_regexp *regexp, int *i, int *j)
{
	char		a;
	char		b;

	a = regexp->value[*j];
	b = regexp->value[*j + 2];
	(*j) += 2;
	while (a <= b)
	{
		if (name[*i] == a)
			return (ERROR);
		a++;
	}
	return (FAILURE);
}

/*
** sh_pattern_matching_brace_dash:
**	Parse content of a brace pattern with for [...a-b...] or [!...a-b...].
**	WARNING : returned values are not as usual, check next section.
**
**	Returned Values:
**		SUCCESS : name[*i] match current pattern
**		ERROR : If pattern is invalid
**		FAILURE : name[*i] do not match current pattern
*/

int			sh_pattern_matching_brace_dash(
	char *name, t_regexp *regexp, int *i, int *j)
{
	char		a;
	char		b;
	int			not;

	not = regexp->value[0] == '!' ? 1 : 0;
	if (not)
		return (sh_pattern_matching_brace_dash_not(name, regexp, i, j));
	a = regexp->value[*j];
	b = regexp->value[*j + 2];
	if (b < a)
		return (ERROR);
	(*j) += 2;
	while (a <= b)
	{
		if (name[*i] == a)
			return (SUCCESS);
		a++;
	}
	return (FAILURE);
}

/*
** sh_pattern_matching_brace_dash:
**	Parse content of a brace pattern with for [...a-b...] or [!...a-b...].
**	WARNING : returned values are not as usual, check next section.
**
**	Returned Values:
**		SUCCESS : name[*i] match current pattern
**		ERROR : If pattern is invalid
**		FAILURE : name[*i] do not match current pattern
*/

int			sh_pattern_matching_brace_simple(
	char *name, t_regexp *regexp, int *i, int *j)
{
	int			not;

	not = regexp->value[0] == '!' ? 1 : 0;
	if (!not && regexp->value[*j] == name[*i])
		return (SUCCESS);
	if (not && regexp->value[*j] == name[*i])
		return (ERROR);
	return (FAILURE);
}
