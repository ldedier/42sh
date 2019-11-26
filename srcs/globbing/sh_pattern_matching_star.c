/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_star.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:49:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 07:01:08 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

static int	star_recursive_check(
	char *name, int *i, t_list *regexp_head)
{
	int		index;
	int		j;
	t_list	*head;

	index = *i;
	while (name[index])
	{
		head = regexp_head->next;
		j = index;
		while (head)
		{
			t_regexp_show_list(head);
			if (sh_globbing_call_pattern_function(name, &j, &head) == ERROR)
				break ;
		}
		if (!head && !name[j])
		{
			*i = index;
			return (SUCCESS);
		}
		index++;
	}
	return (ERROR);
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
	char *name, int *i, t_list *regexp_head)
{
	if (!regexp_head->next)
	{
		while (name[*i])
			(*i) += 1;
		return (SUCCESS);
	}
	return (star_recursive_check(name, i, regexp_head));
}
