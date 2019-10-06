/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_tab_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:39:47 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/07 00:42:04 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_dy_tab_empty(t_dy_tab *table)
{
	int		i;

	i = 0;
	while (table->tbl[i])
	{
		free(table->tbl[i]);
		table->tbl[i] = NULL;
		i++;
	}
	table->current_size = 0;
}
