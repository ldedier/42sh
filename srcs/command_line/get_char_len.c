/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:13:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/20 20:54:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		get_char_len_unprotected(int index, unsigned char *entry)
{
	int i;
	int j;

	i = index;
	j = 1;
	while (j <= 1)
	{
		if (is_printable_utf8(&entry[i], j))
			return (j);
		j++;
	}
	return (-1);
}

int		get_char_len2(int index, int len, unsigned char *entry)
{
	int i;
	int j;

	i = index;
	j = 1;
	while (i + j <= len && j <= 1)
	{
		if (is_printable_utf8(&entry[i], j))
			return (j);
		j++;
	}
	return (-1);
}

int		get_char_len(int index, unsigned char *entry)
{
	int i;
	int j;
	int len;

	i = index;
	j = 1;
	len = ft_strlen((char *)entry);
	while (i + j <= len && j <= 1)
	{
		if (is_printable_utf8(&entry[i], j))
			return (j);
		j++;
	}
	return (-1);
}
