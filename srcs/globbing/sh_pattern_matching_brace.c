/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_brace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:48:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/22 11:57:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	quote(char *str, t_regexp *regexp, int *i, int *j)
{
	int		ret;

	(*j) += 1;
	if (regexp->value[*j - 1] == '\'')
	{
		while (regexp->value[*j] && regexp->value[*j] != '\'')
		{
			ret = sh_pattern_matching_brace_simple(str, regexp, i, j);
			if (ret != FAILURE)
				return (ret);
			(*j) += 1;
		}
	}
	else if (regexp->value[*j - 1] == '\"')
	{
		while (regexp->value[*j] && regexp->value[*j] != '"')
		{
			if (regexp->value[*j] == '\\')
				(j) += 1;
			if ((ret = sh_pattern_matching_brace_simple(str, regexp, i, j)) < 2)
				return (ret);
			(*j) += 1;
		}
	}
	return (FAILURE);
}

static int	backslash(char *name, t_regexp *regexp, int *i, int *j)
{
	int		ret;

	(*j) += 1;
	ret = sh_pattern_matching_brace_simple(name, regexp, i, j);
	if (ret != FAILURE)
		return (ret);
	(*j) += 1;
	return (FAILURE);
}

static int	unquoted(char *name, t_regexp *regexp, int *i, int *j)
{
	int		ret;

	if (regexp->value[*j + 1] == '-' && regexp->value[*j + 2])
		ret = sh_pattern_matching_brace_dash(name, regexp, i, j);
	else
		ret = sh_pattern_matching_brace_simple(name, regexp, i, j);
	(*j) += 1;
	return (ret);
}

static int	sh_pattern_matching_brace_return(int ret, int *i)
{
	if (ret == SUCCESS)
		(*i) += 1;
	return (ret);
}

/*
**	During all process FAILURE return value is considered as a continue
**	looking for matching pattern;
*/

int			sh_pattern_matching_brace(char *name, t_regexp *regexp, int *i)
{
	int		j;
	int		ret;

	j = regexp->value[0] == '!' ? 1 : 0;
	if (!regexp->value[j])
		return (ERROR);
	while (regexp->value[j])
	{
		if (regexp->value[j] == '"' || regexp->value[j] == '\'')
			ret = quote(name, regexp, i, &j);
		else if (regexp->value[j] == '\\')
			ret = backslash(name, regexp, i, &j);
		else
			ret = unquoted(name, regexp, i, &j);
		if (ret == SUCCESS || ret == ERROR)
			return (sh_pattern_matching_brace_return(ret, i));
	}
	if (regexp->value[0] == '!')
	{
		(*i) += 1;
		return (SUCCESS);
	}
	return (ERROR);
}
