/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:39:25 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 07:27:46 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_ptr(char *ptr, size_t current_size, size_t max_size)
{
	t_dy_str	*res;

	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	res->str = ptr;
	res->current_size = current_size;
	res->max_size = max_size;
	return (res);
}
