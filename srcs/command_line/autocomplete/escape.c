/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:55:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/14 14:55:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_should_escape(char c)
{
	return (c == ' ' || c == '\\' || c == '\'' || c == '\"');
}

int			sh_escaped_len(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (sh_should_escape(str[i]))
			len += 2;
		else
			len++;
		i++;
	}
	return (len);
}

void		ft_strcat_escaped(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(dest);
	while (src[i])
	{
		if (sh_should_escape(src[i]))
		{
			dest[j++] = '\\';
			dest[j++] = src[i];
		}
		else
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
}

char		*ft_strdup_escaped(char *str)
{
	char *res;

	if (!(res = ft_strnew(sh_escaped_len(str))))
		return (NULL);
	ft_strcat_escaped(res, str);
	return (res);
}

char		*ft_strjoin_escaped(char *s1, char *s2)
{
	char *res;

	if (!(res = ft_strnew(sh_escaped_len(s1) + sh_escaped_len(s2))))
		return (NULL);
	ft_strcat_escaped(res, s1);
	ft_strcat_escaped(res, s2);
	return (res);
}
