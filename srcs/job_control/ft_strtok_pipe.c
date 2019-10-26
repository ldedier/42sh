/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:56:01 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/25 19:01:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

char		*ft_strtok_pipe(char *str, char *delim)
{
	static char		*buff;
	char			*buff_it;
	char			*token;
	int				count;

	count = 0;
	if (str)
		buff = str;
	while (*buff && ft_strcontains(delim, *buff))
	{
		buff++;
	}
	if (*buff == '\0')
		return (NULL);
	token = buff;
	buff_it = buff;
	while (*buff_it)
	{
		if (*buff_it == '(' || *buff_it == '{')
			count++;
		if (*buff_it == ')' || *buff_it == '}')
			count--;
		if (ft_strcontains(delim, *buff_it) && count == 0)
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