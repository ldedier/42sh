/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_save.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:31:33 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:31:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_save		*t_save_new(char *str, int index)
{
	t_save *res;

	if (!(res = malloc(sizeof(t_save))))
		return (sh_perrorn(SH_ERR1_MALLOC, "t_save_new (1)"));
	res->current_index = index;
	if (!(res->str = ft_strdup(str)))
	{
		free(res);
		return (sh_perrorn(SH_ERR1_MALLOC, "t_save_new (2)"));
	}
	return (res);
}

void		t_save_free(t_save *save)
{
	free(save->str);
	free(save);
}

void		t_save_free_list(void *s, size_t dummy)
{
	t_save *save;

	(void)dummy;
	save = (t_save *)s;
	t_save_free(save);
}
