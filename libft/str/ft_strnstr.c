/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:28:36 by jmartel           #+#    #+#             */
/*   Updated: 2019/08/30 12:03:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strnstr :
**	Locate the first occurence of the null-terminated string find in the string
**	str. No more than len chars are compared.
**
**	returnded Values:
**		NULL : if no occurences were found
**		Address of first char of the first occurence
*/

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t		istr;
	size_t		ifind;

	if (*find == 0)
		return ((char*)str);
	istr = 0;
	while (str[istr] && istr < len)
	{
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind] \
				&& istr + ifind < len)
			ifind++;
		if (find[ifind] == 0 && str[istr] && istr < len)
			return ((char*)(str + istr));
		istr++;
	}
	return (NULL);
}

/*
** ft_strrnstr :
**	Locate the first occurence of the null-terminated string find in the string
**	str, starting by the last character. No more than len chars are compared.
**
**	returnded Values:
**		NULL : if no occurences were found
**		Address of first char of the first occurence
*/

char	*ft_strrnstr(const char *str, const char *find, size_t len)
{
	size_t		istr;
	size_t		ifind;
	size_t		len_str;

	if (*find == 0)
		return ((char*)str);
	len_str = ft_strlen(str);
	istr = len_str;
	while (istr > 0 && len_str - istr <= len)
	{
		istr--;
		ifind = 0;
		while (str[istr + ifind] && str[istr + ifind] == find[ifind]\
			&& len_str - istr <= len)
			ifind++;
		if (find[ifind] == 0 && len_str - istr <= len)
			return ((char*)(str + istr));
	}
	return (NULL);
}
