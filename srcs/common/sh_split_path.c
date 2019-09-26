/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 09:50:53 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/09/26 09:51:02 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	splitlen(char const *path)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	if (path[0] == ':')
		len++;
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || path[i + 1] == '\0')
				len++;
			i++;
		}
		else
		{
			while (path[i] && path[i] != ':')
				i++;
			len++;
		}
	}
	return (len);
}

static char	*what_to_dup(char const *str, int len)
{
	if (len == 0)
		return (ft_strdup("."));
	else
		return (ft_strndup(str, len));
}

static int	splitdup(char **tab_path, char const *path)
{
	int	i;
	int	j;
	int	curr;

	i = 0;
	j = 0;
	curr = 0;
	while (path[i])
	{
		while (path[i + j] && path[i + j] != ':')
			j++;
		if ((tab_path[curr] = what_to_dup(path + i, j)) == NULL)
			return (-1);
		curr++;
		tab_path[curr] = NULL;
		if (path[i + j] && (path[i + j + 1] || j == 0))
			j++;
		i += j;
		j = 0;
	}
	return (0);
}

char		**sh_split_path(char const *path)
{
	int		len;
	char	**tab_path;

	if (!path[0])
		len = 0;
	else
		len = splitlen(path);
	if ((tab_path = malloc((len + 1) * sizeof(char *))) == NULL)
		return (NULL);
	tab_path[0] = NULL;
	if (splitdup(tab_path, path) < 0)
	{
		ft_strtab_free(tab_path);
		return (NULL);
	}
	return (tab_path);
}
