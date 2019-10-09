/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 19:38:06 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/09 05:17:13 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*buf;

	if (!alst || !*alst)
		return ;
	while (*alst != NULL)
	{
		buf = *alst;
		*alst = (*alst)->next;
		if (del)
			del(buf->content, buf->content_size);
		free(buf);
		buf = NULL;
	}
	ft_memdel((void*)alst);
	return ;
}
