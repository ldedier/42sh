/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table_show_perf.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:22:33 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/12 17:22:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_table_show_perf(t_hash_table *table)
{
	size_t		i;
	t_list		*ptr;
	int			len;
	int			nb_data;
	int			nb_collisions;

	nb_data = 0;
	nb_collisions = 0;
	i = 0;
	while (i < table->size)
	{
		if ((ptr = table->data[i]))
		{
			if ((len = ft_lstlen(ptr)) > 1)
			{
				nb_collisions++;
				ft_printf("index #%d:collision of %d elements\n", i, len);
			}
			nb_data += len;
		}
		i++;
	}
	ft_printf("%d element%s in a %d size hash_table with %d collision%s\n",
		nb_data, nb_data == 1 ? "" : "s", table->size, nb_collisions,
			nb_collisions == 1 ? "" : "s");
}
