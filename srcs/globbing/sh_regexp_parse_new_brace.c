/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_brace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:46:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 06:43:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
	regexp->value = value;
	regexp->type = REG_BRACE;
	regexp->start = start;
	regexp->len = ft_strlen(value);
	return (SUCCESS);
}

static void	new_brace_quoted(char *str, int *i, char *quoted)
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

int			sh_regexp_parse_new_brace(char *str, int *i, t_list **regexp_list)
{
	int			start;
	char		quoted;
	int			first_closing;

	start = *i;
	first_closing = -1;
	quoted = 0;
	(*i) += 1;
	if (str[*i] == '!')
		(*i) += 1;
	if (str[*i] == ']' && str[*i + 1])
	{
		first_closing = (*i);
		(*i)++;
	}
	while (str[*i] && str[*i] != ']')
	{
		if (str[*i] == '\'' || str[*i] == '\\' || str[*i] == '"')
		{
			quoted = str[*i];
			(*i) += 1;
		}
		else if (quoted)
			new_brace_quoted(str, i, &quoted);
		else
			(*i)++;
	}
	if (quoted)
		return (ERROR);
	if (!str[*i])
	{
		if (first_closing == -1)
		{
			*i = start;
			return (sh_regexp_parse_new_string(str, i, regexp_list));
		}
		*i = first_closing - 1;
	}
	(*i)++;
	return (create_regexp(regexp_list, str, start, *i));
}
