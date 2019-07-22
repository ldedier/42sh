/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 07:18:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/22 07:44:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char **get_operations(void)
{
	static char *res[NB_OPERATIONS] = {
		"mr",
		"nd",
		"up",
		"cr",
		"do",
		"bl",
		"us",
		"ue",
		"cd",
		"ce",
		"me",
		"cl"
	};
	return (res);
}

int		sh_check_term(void)
{
	int		i;
	char	**operations;

	operations = get_operations();
	i = 0;
	while (i < NB_OPERATIONS)
	{
		if (tgetstr(operations[i], NULL) == NULL)
		{
			ft_dprintf(2, "Terminal rejected because"
				" it does not have the %s capability\n", operations[i]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
