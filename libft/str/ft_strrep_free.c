/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 09:31:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/09/20 16:00:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strrep_free :
**		Replace some chars in s1 by s2 content. Start indicate the first param
**		where do s2 will be introduced, len is number if chars that were in s1,
**		after index start that won't appear in final result.
**		It allocate a new string.
**		return:
**			NULL : if any error occur (can't find pattern, can't allocate mem)
**			address of new string else
*/

char		*ft_strrep(char *s1, char *s2, int start, int len)
{
	char	*res;
	int		i1;
	int		i2;
	int		lenp;

	lenp = (ft_strlen(s1) - len + ft_strlen(s2) + 1);
	if (!(res = malloc(sizeof(*res) * lenp)))
		return (NULL);
	i1 = -1;
	while (++i1 < start)
		res[i1] = s1[i1];
	i2 = -1;
	while (s2[++i2])
		res[i1 + i2] = s2[i2];
	while (s1[i1 + len])
	{
		res[i2 + i1] = s1[i1 + len];
		i1++;
	}
	res[i1 + i2] = 0;
	return (res);
}

/*
** ft_strrep_free :
**		Replace some chars in s1 by s2 content. Start indicate the first param
**		where do s2 will be introduced, len is number if chars that were in s1,
**		after index start that won't appear in final result.
**		It allocate a new string, and s1 is free.
**		return:
**			NULL : if any error occur (can't find pattern, can't allocate mem)
**			address of new string else
*/

char		*ft_strrep_free(char *s1, char *s2, int start, int len)
{
	char	*res;
	int		i1;
	int		i2;
	int		lenp;

	lenp = (ft_strlen(s1) - len + ft_strlen(s2) + 1);
	if (!(res = malloc(sizeof(*res) * lenp)))
		return (NULL);
	i1 = -1;
	while (++i1 < start)
		res[i1] = s1[i1];
	i2 = -1;
	while (s2[++i2])
		res[i1 + i2] = s2[i2];
	while (s1[i1 + len])
	{
		res[i2 + i1] = s1[i1 + len];
		i1++;
	}
	res[i1 + i2] = 0;
	free(s1);
	return (res);
}

/*
** ft_strrep_pattern_free : look for pattern in s1, and replace it by s2
**		It allocate a new string, you can use param to free any arguments
**		param:
**			if param & 0x0001 : free s1
**			if param & 0x0002 : free s2
**			if param & 0x0004 : free pattern
**		return:
**			NULL : if any error occur (can't find pattern, can't allocate mem)
**			Else : address of new string
*/

static void	ft_strrep_pattern_free_free(
	char *s1, char *s2, char *pattern, int param)
{
	if (param & 0x0001)
		free(s1);
	if (param & 0x0002)
		free(s2);
	if (param & 0x0004)
		free(pattern);
}

char		*ft_strrep_pattern_free(
	char *s1, char *s2, char *pattern, int param)
{
	char	*res;
	int		i1;
	int		i2;
	int		lenp;
	char	*pt;

	if (!(pt = ft_strstr(s1, pattern)))
		return (NULL);
	lenp = (ft_strlen(s1) + ft_strlen(s2) - ft_strlen(pattern) + 1);
	if (!(res = malloc(sizeof(*res) * lenp)))
		return (NULL);
	i1 = -1;
	while (s1 + ++i1 != pt)
		res[i1] = s1[i1];
	i2 = -1;
	while (s2[++i2])
		res[i1 + i2] = s2[i2];
	lenp = ft_strlen(pattern);
	i1--;
	while (s1[++i1 + lenp])
		res[i1 + i2] = s1[i1 + lenp];
	res[i1 + i2] = 0;
	ft_strrep_pattern_free_free(s1, s2, pattern, param);
	return (res);
}
