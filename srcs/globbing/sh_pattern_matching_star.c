/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_star.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 04:49:08 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 04:56:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_pattern_matching_star(char *name, t_regexp *regexp, int *i, t_list *regexp_head)
{
	t_regexp	*next_regexp;
	char		*buff;
	char		save;

	if (!regexp_head->next)
	{
		while (name[*i])
			(*i) += 1;
		// ft_dprintf(2, "no new regexp : i : %i\n", *i);
		return (SUCCESS);
	}
	next_regexp = (t_regexp*)regexp_head->next->content;
	if (next_regexp->type == REG_STAR)
		return (SUCCESS);
	else if (next_regexp->type == REG_STR)
	{
		save = next_regexp->value[next_regexp->len];
		next_regexp->value[next_regexp->len] = '\0';
		// ft_dprintf(2, "looking for %s in : %s\n", next_regexp->value, name + *i);
		if ((buff = ft_strrstr(name + *i, next_regexp->value)))
		{
			next_regexp->value[next_regexp->len] = save;
			(*i) += buff - (name + *i);
			// ft_dprintf(2, "new i : %d (%c)\n", *i, name[*i]);
			return (SUCCESS);
		}
		next_regexp->value[next_regexp->len] = save;
		return (ERROR);
	}
	else if (next_regexp->type == REG_QUEST)
	{
		if (sh_pattern_matching_star(name, regexp, i, regexp_head->next))
			return (ERROR);
		(*i)--;
		return (SUCCESS);
	}
	else if (next_regexp->type == REG_BRACE)
	{
		int		j;
	
		j = ft_strlen(name) - 1;
		// ft_dprintf(2, "i : %d || j : %d\n", *i, j);
		while (j >= (*i) && sh_pattern_matching_brace(name, next_regexp, &j))
		{
			// ft_dprintf(2, "bracket do not feat : %c\n", name[j]);
			j--;
		}
		if (j <= (*i))
			return (ERROR);
		(*i) = j - 1;
		// ft_dprintf(2, "new i : %d || name[i] : %c\n", *i, name[*i]);
		return (SUCCESS);
	}
	return (ERROR);
}
