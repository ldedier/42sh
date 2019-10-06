/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dy_str_new_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:43:40 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/05 07:21:39 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dy_str	*ft_dy_str_new_str(char *str)
{
	t_dy_str	*res;
	size_t		len;

	len = ft_strlen(str);
	if (!(res = malloc(sizeof(*res))))
		return (NULL);
	if (!(res->str = ft_strdup(str)))
	{
		free(res);
		return (NULL);
	}
	res->max_size = len + 1;
	res->current_size = len;
	return (res);
}
