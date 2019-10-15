/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:07:01 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/23 18:05:41 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtok(char *str, char *delim)
{
	static char		*buff;
	char			*buff_it;
	char			*token;

	if (str)
		buff = str;
	while (*buff && ft_strcontains(delim, *buff))
		buff++;
	if (*buff == '\0')
		return (NULL);
	token = buff;
	buff_it = buff;
	while (*buff_it)
	{
		if (ft_strcontains(delim, *buff_it))
		{
			*buff_it = '\0';
			buff = buff_it + 1;
			return (token);
		}
		buff_it++;
	}
	buff = buff_it;
	return (token);
}
