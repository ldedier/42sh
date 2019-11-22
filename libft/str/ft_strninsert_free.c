/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strninsert_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:40:35 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/22 12:23:51 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strninsert_init(char **str, int *or_len, int nb)
{
	char	*tmp;

	*or_len = ft_strlen(*str);
	if ((tmp = malloc((*or_len + nb + 1) * sizeof(char))) == NULL)
	{
		ft_strdel(str);
		return (NULL);
	}
	tmp[0] = 0;
	return (tmp);
}

static void	strinsert_end_loop(char *tmp, int *pos, char c, int i)
{
	tmp[pos[i] + i] = c;
	tmp[pos[i] + i + 1] = 0;
}

/*
** This function will insert nb character c at position occurende in tab
**  in the string str. And free the old str.
**
** Postion in array pos MUST be sort from the lowest to the bigest postion.
** Postion in array pos MUST be contained in size of str + 1.
**
** Returned value :
** 0 if succeed
** -1 if an error occured
*/

int			ft_strninsert_free(char **str, int *pos, char c, int nb)
{
	char	*tmp;
	int		i;
	int		start;
	int		or_len;

	i = 0;
	start = 0;
	if ((tmp = strninsert_init(str, &or_len, nb)) == NULL)
		return (-1);
	while (i < nb && pos[i] < or_len)
	{
		tmp = ft_strncat(tmp, *str + start, pos[i] - start);
		tmp[pos[i] + i] = c;
		tmp[pos[i] + i + 1] = 0;
		start = pos[i];
		i++;
	}
	tmp = ft_strcat(tmp, *str + start);
	if (i < nb)
		strinsert_end_loop(tmp, pos, c, i);
	free(*str);
	*str = tmp;
	return (0);
}
