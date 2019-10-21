/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_brace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:48:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 07:46:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_pattern_matching_brace_dash_not(char *name, t_regexp *regexp, int *i, int *j)
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
	return (SUCCESS);
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

static int	sh_pattern_matching_brace_dash(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	char		a;
	char		b;

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
static int	sh_pattern_matching_brace_simple(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	if (!not && regexp->value[*j] == name[*i])
		return (SUCCESS);
	if (not && regexp->value[*j] == name[*i])
		return (ERROR);
	return (FAILURE);
}

static int	simple_quote(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	int		ret;

	while (regexp->value[*j] && regexp->value[*j] != '\'')
	{
		ret = sh_pattern_matching_brace_simple(name, regexp, i, j, not);
		if (ret != FAILURE)
			return (ret);
		*j += 1;
	}
	return (FAILURE);
}

static int	double_quote(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	int		ret;

	while (regexp->value[*j] && regexp->value[*j] != '"')
	{
		if (regexp->value[*j] == '\\')
			(j) += 1;
		ret = sh_pattern_matching_brace_simple(name, regexp, i, j, not);
		if (ret != FAILURE)
			return (ret);
		(*j) = 1;
	}
	return (FAILURE);
}

static int	backslash(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	int		ret;

	(*j) += 1;
	ret = sh_pattern_matching_brace_simple(name, regexp, i, j, not);
	if (ret != FAILURE)
		return (ret);
	(*j)++;
	return (FAILURE);
}

static int	unquoted(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	int		ret;

	if (regexp->value[*j + 1] == '-' && regexp->value[*j + 2])
		ret = sh_pattern_matching_brace_dash(name, regexp, i, j, not);
	else
		ret = sh_pattern_matching_brace_simple(name, regexp, i, j, not);
	(*j) += 1;
	return (ret);
}

/*
** During all process FAILURE return value is considered as a continue looking for matching pattern;
*/
int			sh_pattern_matching_brace(char *name, t_regexp *regexp, int *i)
{
	int		not;
	int		j;
	int		ret;
	char	quoted;

	j = 1;
	quoted = 0;
	not = regexp->value[j] == '!' && j++ ? 1 : 0;
	if (regexp->value[j] == ']' && !regexp->value[j + 1])
		return (ERROR);
	while (regexp->value[j] && regexp->value[j + 1])
	{
		if (regexp->value[j] == '"')
			ret = double_quote(name, regexp, i, &j, not);
		else if (regexp->value[j] == '\'')
			ret = simple_quote(name, regexp, i, &j, not);
		else if (regexp->value[j] == '\\')
			ret = backslash(name, regexp, i, &j, not);
		else
			ret = unquoted(name, regexp, i, &j, not);
		if (ret == SUCCESS || ret == ERROR)
		{
			if (ret == SUCCESS)
				(*i) += 1;
			return (ret);
		}
	}
	if (not) // check value[j] content ? 
	{
		(*i) += 1;
		return (SUCCESS);
	}
	return (ERROR);
}
