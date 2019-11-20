/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_get_command_to_execute.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:38:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:38:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		ft_substitute_occurences_len(char *str,
	char *to_replace, char *replacement)
{
	int		nb_replacement;
	char	*str_ptr;
	int		to_replace_len;
	int		replacement_len;
	int		str_len;

	to_replace_len = ft_strlen(to_replace);
	replacement_len = ft_strlen(replacement);
	str_len = ft_strlen(str);
	if (to_replace_len == replacement_len)
		return (str_len);
	str_ptr = str;
	nb_replacement = 0;
	while ((str_ptr = ft_strstr(str_ptr, to_replace)))
	{
		str_ptr += to_replace_len;
		nb_replacement++;
	}
	return (str_len + nb_replacement
		* (replacement_len - to_replace_len));
}

static int		ft_memcpy_ret(char *dest, char *src, int n)
{
	ft_memcpy(dest, src, n);
	return (n);
}

char			*ft_substitute_occurences(char *str,
	char *to_replace, char *replacement)
{
	char	*res;
	int		i;
	char	*str_ptr;
	char	*str_ptr_prev;
	int		to_replace_len;

	if (!(res = ft_strnew(ft_substitute_occurences_len(str,
		to_replace, replacement))))
	{
		return (NULL);
	}
	i = 0;
	str_ptr_prev = str;
	str_ptr = str;
	to_replace_len = ft_strlen(to_replace);
	while ((str_ptr = ft_strstr(str_ptr, to_replace)))
	{
		i += ft_memcpy_ret(&res[i], str_ptr_prev, str_ptr - str_ptr_prev);
		i += ft_memcpy_ret(&res[i], replacement, ft_strlen(replacement));
		str_ptr += to_replace_len;
		str_ptr_prev = str_ptr;
	}
	i += ft_memcpy_ret(&res[i], str_ptr_prev, ft_strlen(str_ptr_prev));
	res[i] = '\0';
	return (res);
}

char			*get_command_to_execute_fc(char *command,
	char *substitution_str)
{
	char	*to_replace;
	char	*replacement;
	int		equal_index;
	char	*res;

	if (!substitution_str)
		return (ft_strdup(command));
	else
	{
		equal_index = ft_strichr(substitution_str, '=');
		if (!(to_replace = ft_strndup(substitution_str, equal_index)))
			return (NULL);
		if (!(replacement = ft_strdup(&substitution_str[equal_index + 1])))
		{
			free(to_replace);
			return (NULL);
		}
		if (!(res = ft_substitute_occurences(command,
				to_replace, replacement)))
			return (ft_free_turn_strs(&replacement, &to_replace, NULL));
		free(replacement);
		free(to_replace);
		return (res);
	}
}
