/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_duplicate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:32:43 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/25 10:43:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		free_string_tab(char **str_tab)
{
	int		i;

	if (str_tab == NULL)
		return ;
	i = 0;
	while (str_tab[i] != NULL)
	{
		ft_strdel(str_tab + i);
		i++;
	}
}

char			**str_tab_duplicate(char **from)
{
	int		i;
	char	**to;

	i = 0;
	if (from == NULL)
		return (NULL);
	while (from[i])
		i++;
	if ((to = malloc((i + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = 0;
	while (from[i] != NULL)
	{
		to[i] = ft_strdup(from[i]);
		if (to[i] == NULL)
		{
			free_string_tab(to);
			return (NULL);
		}
		i++;
	}
	to[i] = NULL;
	return (to);
}
