/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_brace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:48:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 04:56:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

static int	sh_pattern_matching_brace_dash(char *name, t_regexp *regexp, int *i, int *j)
{
	char		a;
	char		b;

	a = regexp->value[*j];
	b = regexp->value[*j + 2];
	// ft_dprintf(2, "name : %s |||| a : %c || b : %c || not : %d\n", name + *i, a, b, not);
	if (b < a)
		return (ERROR);
	(*j) += 2;
	while (a <= b)
	{
		if (name[*i] == a)
		{
			(*i) += 1;
			return (SUCCESS);
		}
		a++;
	}
	return (FAILURE);
}

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

int			sh_pattern_matching_brace(char *name, t_regexp *regexp, int *i)
{
	int		not;
	int		j;
	int		ret;

	j = 1;
	not = regexp->value[j] == '!' && j++ ? 1 : 0;
	if (regexp->value[j] == ']' && !regexp->value[j + 1])
		return (ERROR);
	while (regexp->value[j] && regexp->value[j] != ']')
	{
		if (regexp->value[j + 1] == '-' && regexp->value[j + 2])
		{
			if (not)
			{
				if (sh_pattern_matching_brace_dash_not(name, regexp, i, &j))
					return (ERROR);
			}
			else
			{
				ret = sh_pattern_matching_brace_dash(name, regexp, i, &j);
				if (ret == SUCCESS || ret == ERROR)
					return (ret);
			}
		}
		else
		{
			if (!not && regexp->value[j] == name[*i])
			{
				(*i) += 1;
				return (SUCCESS);
			}
			if (not && regexp->value[j] == name[*i])
				return (ERROR);
		}
		j++;
	}
	if (not) // check value[j] content ? 
	{
		(*i) += 1;
		return (SUCCESS);
	}
	return (ERROR);
}
