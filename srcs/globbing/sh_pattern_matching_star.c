/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_star.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:49:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 01:37:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** next_is_str:
**	If next regexp is a string, name shall contain this constant,
**	if it does not pattern cannot be fitted.
**
**	Returned Values
**		SUCCESS : Pattern can fit
**		ERROR : Can't find coinstant in name
*/

static int	next_is_str(char *name, int *i, t_regexp *next_regexp)
{
	char	*buff;

	next_regexp->value[next_regexp->len] = '\0';
	if ((buff = ft_strrstr(name + *i, next_regexp->value)))
	{
		(*i) += buff - (name + *i);
		return (SUCCESS);
	}
	return (ERROR);
}

/*
** next_is_quest:
**	If next pattern is a question mark, next patterns shall imply that there
**	are at least one char in result. So we recursively call
**	pattern_matching_star to check it result.
**	We need then to cancel modification by decrementing i.
**
**	Returned Values
**		SUCCESS : Pattern can fit
**		ERROR : Pattern do not fit
*/

static int	next_is_quest(
	char *name, t_regexp *regexp, int *i)
{
	if (sh_pattern_matching_quest(name, regexp, i))
		return (ERROR);
	(*i)--;
	return (SUCCESS);
}

/*
** next_is_brace:
**	To fit a brace pattern, we are browsing name, starting by the end.
**	While sh_pattern_matching_brace do not return SUCCESS, this means
**	star pattern cannot fit. If we end loop without success, star pattern
**	cannot fit.
**
**	Returned Values
**		SUCCESS : Pattern can fit
**		ERROR : Pattern do not fit
*/

static int	next_is_brace(char *name, t_regexp *next_regexp, int *i)
{
	int		j;

	j = ft_strlen(name) - 1;
	while (j >= (*i) && sh_pattern_matching_brace(name, next_regexp, &j))
	{
		j--;
	}
	if (j < (*i))
		return (ERROR);
	(*i) = j - 1;
	return (SUCCESS);
}

/*
** sh_pattern_matching_star:
**	Star mechanism is based on next pattern. If star is the last pattern,
**	then it is obviously valid. Else it must be studied depending on next
**	pattern type.
**
**	Returned Values
**		SUCCESS : Star pattern can be matched.
**		ERROR : Can't match.
*/

int			sh_pattern_matching_star(
	char *name, t_regexp *regexp, int *i, t_list *regexp_head)
{
	t_regexp	*next_regexp;

	if (!regexp_head->next)
	{
		while (name[*i])
			(*i) += 1;
		return (SUCCESS);
	}
	next_regexp = (t_regexp*)regexp_head->next->content;
	if (next_regexp->type == REG_STAR)
		return (SUCCESS);
	else if (next_regexp->type == REG_STR)
		return (next_is_str(name, i, next_regexp));
	else if (next_regexp->type == REG_QUEST)
		return (next_is_quest(name, regexp, i));
	else if (next_regexp->type == REG_BRACE)
		return (next_is_brace(name, next_regexp, i));
	return (ERROR);
}
