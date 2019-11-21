/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse_new_brace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:46:18 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 12:22:41 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** create_regexp:
**	Malloc and fill a t_list, containing a malloced t_regexp structure.
**	regexp struct is filled using params given as argument.
**	Using i - start - 1 in strndup not to copy the closing ']'.
**
**	Returned Values
**		SUCCESS
**		FAILURE : malloc error
*/

static int	create_regexp(t_list **regexp_list, char *str, int start, int i)
{
	t_regexp	*regexp;
	char		*value;

	if (!(value = ft_strndup(str + start, i - start - 1)))
		return (FAILURE);
	if (!(regexp = t_regexp_new_push(regexp_list)))
	{
		free(value);
		return (FAILURE);
	}
	regexp->value = value;
	regexp->type = REG_BRACE;
	regexp->len = ft_strlen(value);
	return (SUCCESS);
}

static void	new_brace_quoted(char *str, int *i, char *quoted)
{
	while (str[*i] && str[*i] != *quoted)
		(*i) += 1;
	if (str[*i])
	{
		(*i) += 1;
		*quoted = 0;
	}
}

static void	parse_new_brace_find_end_init(
	char *str, int *i, int *first_closing, char *quoted)
{
	*first_closing = -1;
	*quoted = 0;
	(*i) += 1;
	if (str[*i] == '!')
		(*i) += 1;
	if (str[*i] == ']' && str[*i + 1])
	{
		*first_closing = (*i);
		(*i)++;
	}
}

/*
** parse_new_brace_find_end:
**	Browse str string, filling i, first_closing and quoted, until it find an
**	error, or end of a valid brace pattern.
**	Content of these variables will be used by sh_regexp_new_brace to
**	determine if pattern is valid, and it's value.
*/

static void	parse_new_brace_find_end(
	char *str, int *i, int *first_closing, char *quoted)
{
	parse_new_brace_find_end_init(str, i, first_closing, quoted);
	while (str[*i] && str[*i] != ']')
	{
		if (*quoted)
			new_brace_quoted(str, i, quoted);
		else if (str[*i] == '\\')
		{
			(*i) += 1;
			if (str[*i])
				(*i) += 1;
			*quoted = 0;
		}
		else if (str[*i] == '\'' || str[*i] == '"')
		{
			*quoted = str[*i];
			(*i) += 1;
		}
		else
			(*i)++;
	}
}

/*
** sh_regexp_parse_new_brace:
**	Read in string str looking for a valid brace pattern. If any valid pattern
**	is found it creates a new t_regexp struct pushed at the end of regexp_list.
**	A valid brace shall be [A-x], [abc], [!abc], [!A-xabc], ...
**	Brace patterns values are stored without '[' and ']' chars.
**	Quoting shall be respected in brace patterns parsing.
**	If no closing ']' is found, a constant string pattern is delimited.
**
**	Returned Values
**		SUCCESS : Add a t_regep struct defining the brace pattern
**		ERROR : Can't parse pattern, need to cancel globbing process
**		FAILURE : Malloc error
*/

int			sh_regexp_parse_new_brace(char *str, int *i, t_list **regexp_list)
{
	int			start;
	char		quoted;
	int			first_closing;

	start = *i + 1;
	parse_new_brace_find_end(str, i, &first_closing, &quoted);
	if (quoted)
		return (ERROR);
	if (!str[*i])
	{
		if (first_closing == -1)
		{
			*i = start - 1;
			return (LEX_CONTINUE);
		}
		*i = first_closing - 1;
	}
	(*i) += 1;
	return (create_regexp(regexp_list, str, start, *i));
}
