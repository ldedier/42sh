/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:56:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/14 14:55:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		copy_str_to_res(char *res, char *str, int *i, int to_add)
{
	while (to_add--)
	{
		res[*i] = str[*i];
		*i += 1;
	}
}

int			ft_isprint_only_utf8(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] & 0b10000000))
		{
			if (!ft_isprint(str[i++]))
				return (0);
		}
		else if (str[i] & 0b01000000 && !(str[i] & 0b00100000))
			return (0);
		else if (str[i] & 0b00100000 && !(str[i] & 0b00010000))
			return (0);
		else if (str[i] & 0b000100000 && !(str[i] & 0b00001000))
			return (0);
		else
			i++;
	}
	return (1);
}

char		*ft_str_to_ascii_dup(char *str)
{
	int		i;
	char	*res;

	if (!(res = malloc(sizeof(char ) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (!(str[i] & 0b10000000))
		{
			res[i] = (ft_isprint(str[i]) ? str[i] : '?');
			i++;
		}
		else if (str[i] & 0b01000000 && !(str[i] & 0b00100000))
			copy_str_to_res(res, str, &i, 2);
		else if (str[i] & 0b00100000 && !(str[i] & 0b00010000))
			copy_str_to_res(res, str, &i, 3);
		else if (str[i] & 0b000100000 && !(str[i] & 0b00001000))
			copy_str_to_res(res, str, &i, 4);
		else
			i++;
	}
	res[i] = '\0';
	return (res);
}

int			populate_file(t_file *file, char *name, char **path, t_shell *shell)
{
	if (!(file->name = ft_strdup_escaped(name)))
	{
		free(file);
		return (1);
	}
	if (!(*path = ft_strdup_escaped(file->fullname)))
	{
		free(file);
		return (1);
	}
	if (!ft_strncmp(*path, "~/", 2)
			&& process_subst_home(shell, path))
	{
		free(*path);
		free(file);
		return (1);
	}
	return (0);
}

t_file		*new_file(t_shell *shell, char *name, char *fullname)
{
	t_file	*res;
	char	*path;

	(void)shell;
	if (!(res = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	res->x = 0;
	res->y = 0;
	if (!(res->fullname = ft_strdup_escaped(fullname)))
		return (ft_free_turn_ptr(res));
	if (populate_file(res, name, &path, shell))
	{
		free(res->fullname);
		free(res);
		return (NULL);
	}
	if (stat(fullname, &res->st) == -1)
		res->unstatable = 1;
	else
		res->unstatable = 0;
	free(path);
	free(fullname);
	return (res);
}
