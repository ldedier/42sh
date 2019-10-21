/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:34:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 05:54:07 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	remove_quotes_in_value(char *str)
{
	int			i;
	char		quoted;

	i = 0;
	quoted = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\\' || str[i] == '"')
		{
			quoted = str[i];
			ft_strdelchar(str, i);
		}
		else if (quoted == '\\')
		{
			i++;
			quoted = 0;
		}
		else if (quoted)
		{
			while (str[i] != quoted)
				i++;
			ft_strdelchar(str, i);
		}
		else
			i += 1;
	}
}

static int	create_regexp(t_list **regexp_list, char *str, int start, int i)
{
	t_regexp	*regexp;
	char		*value;

	if (!(value = ft_strndup(str + start, i - start)))
		return (FAILURE);
	if (!(regexp = t_regexp_new_push(regexp_list)))
	{
		free(value);
		return (FAILURE);
	}
	regexp->type = REG_STR;
	regexp->start = start;
	regexp->value = value;
	remove_quotes_in_value(value);
	regexp->len = ft_strlen(value);
	return (SUCCESS);
}

static void	new_string_quoted(char *str, int *i, char *quoted)
{
	if (*quoted == '\\')
	{
		(*i) += 1;
		*quoted = 0;
	}
	else
	{
		while (str[*i] && str[*i] != *quoted)
			(*i) += 1;
		if (str[*i])
		{
			(*i) += 1;
			*quoted = 0;
		}
	}
}

int			sh_regexp_parse_new_string(char *str, int *i, t_list **regexp_list)
{
	int			start;
	char		quoted;

	start = *i;
	if (str[*i] == '[')
		(*i) += 1;
	quoted = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\\' || str[*i] == '"')
		{
			quoted = str[*i];
			(*i) += 1;
		}
		else if (quoted)
			new_string_quoted(str, i, &quoted);
		else if (str[*i] == '?' || str[*i] == '[' || str[*i] == '*')
			break ;
		else
			(*i) += 1;
	}
	if (quoted)
		return (ERROR);
	return (create_regexp(regexp_list, str, start, *i));
}
