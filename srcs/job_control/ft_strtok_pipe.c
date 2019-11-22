/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:56:01 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 10:09:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		init_value(int *count, char *str, char **buff, char *delim)
{
	*count = 0;
	if (str)
		*buff = str;
	while (**buff && ft_strcontains(delim, **buff))
		(*buff)++;
}

static void		handle_paranthesis(char c, int *count)
{
	if (c == '(' || c == '{')
		(*count)++;
	if (c == ')' || c == '}')
		(*count)--;
}

char			*ft_strtok_pipe(char *str, char *delim)
{
	static char		*buff;
	char			*buff_it;
	char			*token;
	int				count;

	init_value(&count, str, &buff, delim);
	if (*buff == '\0')
		return (NULL);
	token = buff;
	buff_it = buff;
	while (*buff_it)
	{
		handle_paranthesis(*buff_it, &count);
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
