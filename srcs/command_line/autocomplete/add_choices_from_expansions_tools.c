/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_from_expansions_tools.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:32:19 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:32:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** returns 0 if the entry does not match with the comparison
** returns 1 if the entry key match with the comparison
** returns 2 if the entry key is equal to the comparison
**
** updates the index of the equal character of the entry throughout the process
*/

int		sh_match_key(char *entry, char *to_compare, int *equal_index)
{
	int i;

	i = 0;
	*equal_index = 0;
	while (to_compare[i] && entry[i] != '=')
	{
		if (entry[i] != to_compare[i])
			return (0);
		i++;
	}
	if (entry[i] == '=' && !to_compare[i])
	{
		*equal_index = i;
		return (2);
	}
	else if (!to_compare[i])
	{
		while (entry[i] != '=')
			i++;
		*equal_index = i;
		return (1);
	}
	return (0);
}

int		get_end_index(char *str, int index)
{
	while (str[index] && str[index] != '$')
		index++;
	return (index);
}

int		free_turn_choice_filler(t_choice_filler *c, int ret)
{
	ft_strdel(&c->suffix);
	ft_strdel(&c->path);
	return (ret);
}
