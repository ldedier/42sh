/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_string.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:34:30 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 11:39:53 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** remove_quotes_in_value:
**	Classic function, used to remove quotes in a string str, parsing quotes.
**	i and quoted arguments shall always be initialized as 0.
**	Function assume that quoting had been verified and is correct.
**	Ternary means : if a backslash is between double quotes, it keeps it
**		escaping char role, and it will be deleted.
*/

static void	remove_quotes_in_value(char *str, int i, char quoted)
{
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
				quoted == '"' && str[i] == '\\' ? ft_strdelchar(str, i++) : i++;
			quoted = 0;
			ft_strdelchar(str, i);
		}
		else
			i += 1;
	}
}

/*
** create_regexp:
**	Malloc and fill a t_list, containing a malloced t_regexp structure.
**	regexp struct is filled using params given as argument.
**
**	Returned Values
**		SUCCESS
**		FAILURE : malloc error
*/

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
	regexp->value = value;
	remove_quotes_in_value(value, 0, 0);
	regexp->len = ft_strlen(value);
	return (SUCCESS);
}

/*
** new_string_quoted:
**	Function used in sh_regexp_parse_new_string.
**	If given quoted char is a '\', it goes to next char,
**	else it browse str, looking for closing quote.
*/

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

/*
** sh_regexp_parse_new_string:
**	Read a string str to check that content can be parsed a constant string
**	pattern. It implies to manually check quoting in the string.
**	If pattern is considered as valid a t_regexp struct, correctly filled, is
**	added at the end of regexep_list.
**
**	Returned Values
**		SUCCESS : Successfully added a string t_regexp to list
**		ERROR : Problem parsing quotes (end parsing with unclosed quotes)
**		FAILURE : Malloc error
*/

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
