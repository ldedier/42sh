/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew_ptr_last_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 21:45:23 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/23 21:45:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstaddnew_ptr_last_list(t_list **list,
				void *content, size_t size, t_list **last_item_ptr)
{
	t_list *node;

	if (!(node = ft_lstnew(content, size)))
		return (1);
	if (*last_item_ptr)
		ft_lstadd_last(last_item_ptr, node);
	else
		ft_lstadd(list, node);
	*last_item_ptr = node;
	return (0);
}
