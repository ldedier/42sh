/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_side.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:34:27 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 01:57:52 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istrim(char c, char *charset)
{
	if (ft_strchr(charset, c))
		return (1);
	else
		return (0);
}

/*
** Return the index of the first non-whitespace character in 'str'.
*/

static int	get_leading_index(char *str, char *charset)
{
	int		i;

	i = 0;
	while (str[i] && ft_istrim(str[i], charset))
		i++;
	return (i);
}

/*
** Return the index of the last non-whitespace character in 'str'.
*/

static int	get_trailing_index(char *str, char *charset)
{
	size_t	len;
	int		i;

	len = ft_strlen(str);
	i = (int)len - 1;
	while (i >= 0 && ft_istrim(str[i], charset))
		i--;
	return (i);
}

/*
** Trim leading or/and trailing characters depending on the 'side' argument.
** @str:		Original string (Will be modifed and returned, do not free).
** @charset:	Set of characters we want to remove.
** @side:		1			->	trim leading characters.
** @side:		2			->	trim trailing characters.
** @side:		3			->	trime both leading and trailing characters.
** @side:		otherwise	->	trim nothing.
*/

char		*ft_strtrim_side(char *str, char *charset, int side)
{
	char	*res;
	size_t	len;
	int		start;
	int		end;

	if (str == NULL)
		return (NULL);
	if (side < 1 || side > 3)
		return (str);
	len = ft_strlen(str);
	start = 0;
	end = len - 1;
	if (side & 1)
		start = get_leading_index(str, charset);
	if (side & 2)
		end = get_trailing_index(str, charset);
	res = ft_strndup(str + start, end - start + 1);
	free(str);
	return (res);
}
