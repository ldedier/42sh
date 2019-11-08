/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:59:55 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/20 06:44:43 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strjoin_path_free:
**	Call ft_strjoin_path, and free s1 and / or s2, using opt
**	If opt & 0x01 is true : free s1
**	If opt & 0x02 is true : free s2
**
**	Return Value:
**		NULL : malloc error or s1 and s2 are NULL
**		Else : Address of new malloced string
*/

char		*ft_strjoin_path_free(char *s1, char *s2, int opt)
{
	char	*res;

	res = ft_strjoin_path(s1, s2);
	if (opt & 0x01 && s1)
		free(s1);
	if (opt & 0x02 && s2)
		free(s2);
	return (res);
}

/*
** ft_strjoin_path:
**	Try to create a path by concatenating s1 and s2, adding '/' if needed
**
**	Return Value:
**		NULL : malloc error or s1 and s2 are NULL
**		Else : Address of new malloced string
*/

char		*ft_strjoin_path(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL || *s1 == 0)
		return (ft_strdup(s2));
	else if (s2 == NULL || *s2 == 0)
		return (ft_strdup(s1));
	if (s1[ft_strlen(s1) - 1] == '/')
		return (ft_strjoin_free(s1, s2, 0));
	res = (char*)malloc(sizeof(*res) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = '/';
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}
