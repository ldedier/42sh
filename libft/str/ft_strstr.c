/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:28:13 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 01:57:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strstr :
**	Locate the first occurence of the null-terminated string find in the string
**	str.
**
**	returnded Values:
**		NULL : if no occurences were found
**		Address of first char of the first occurence found
*/

char	*ft_strstr(const char *str, const char *find)
{
	size_t		istr;
	size_t		ifind;

	if (*find == 0)
		return ((char*)str);
	istr = 0;
	while (str[istr])
	{
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind])
			ifind++;
		if (find[ifind] == 0 && str[istr])
			return ((char*)(str + istr));
		istr++;
	}
	return (NULL);
}

/*
** ft_strrstr :
**	Locate the first occurence of the null-terminated string find in the string
**	str, starting by the last character.
**
**	returnded Values:
**		NULL : if no occurences were found
**		Address of first char of the first occurence found
*/

char	*ft_strrstr(const char *str, const char *find)
{
	size_t		istr;
	size_t		ifind;
	size_t		len_str;

	if (*find == 0)
		return ((char*)str);
	len_str = ft_strlen(str);
	istr = len_str;
	while (istr > 0)
	{
		istr--;
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind])
			ifind++;
		if (find[ifind] == 0)
			return ((char*)(str + istr));
	}
	return (NULL);
}
