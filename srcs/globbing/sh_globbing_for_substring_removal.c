/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_globbing_for_substring_removal.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 05:50:11 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/21 16:46:29 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** parse_patterns:
**
**	Returned Values
**		SUCCESS : Successfully performed parsing
**		ERROR : Error in parsing that shall cancel globbing process
**		FAILURE : Malloc error
*/

static int	parse_patterns(char *word, t_list **regexp_list)
{
	int	ret;

	*regexp_list = NULL;
	if ((ret = sh_regexp_parse_path_component(word, regexp_list)))
	{
		if (*regexp_list)
			ft_lstdel(regexp_list, &t_regexp_free);
	}
	return (ret);
}

/*
** prefix_pattern_matching:
**	Look any substring in param that can match patterns described in
**	regexp_list. Look starts at the begining of param string.
**	If format is "#" the smallest matching substring is stored.
**	If format is "##" the longest matching substring is stored.
**	Matching string is stored in *index, as the len of the selected substring.
*/

static void	prefix_pattern_matching(
	char *param, int *index, t_list *regexp_list, char *format)
{
	int		i;
	char	save;
	int		len;

	i = 0;
	len = ft_strlen(param);
	while (i <= len)
	{
		save = param[i];
		param[i] = '\0';
		if (sh_is_pattern_matching_for_substring_removal(
			param, regexp_list) == SUCCESS)
		{
			param[i] = save;
			*index = i;
			if (sh_verbose_globbing())
				ft_dprintf(2, GREEN"\tmatched : %s\n"EOC, param);
			if (format[1] == '\0')
				break ;
		}
		param[i] = save;
		i++;
	}
}

/*
** suffix_pattern_matching:
**	Look any substring in param that can match patterns described in
**	regexp_list. Look starts at the end of param string.
**	If format is "%" the smallest matching substring is stored.
**	If format is "%%" the longest matching substring is stored.
**	Matching string is stored in *index, as the start of the selected substring.
*/

static void	suffix_pattern_matching(
	char *param, int *index, t_list *regexp_list, char *format)
{
	int		i;

	i = ft_strlen(param);
	while (i >= 0)
	{
		if (sh_is_pattern_matching_for_substring_removal(
			param + i, regexp_list) == SUCCESS)
		{
			*index = i;
			if (sh_verbose_globbing())
				ft_dprintf(2, GREEN"\tmatched : %s\n"EOC, param + i);
			if (format[1] == '\0')
				break ;
		}
		i--;
	}
}

/*
** sh_globbing_for_substring_removal:
**	Parse word to create a t_list containing t_regexp describing word content.
**	Then it check if this patterns can match param content. Research functions
**	are different depending if we are looking for prefix (#) or suffix (%).
**	Result is stored in index variable (see pattern_matching functions above).
**
**	Returned Values
**		SUCCESS : Successfully performed pattern matching
**		ERROR : Error in parsing, shall not process pattern_matching process
**		FAILURE : Malloc error
*/

static int	sh_globbing_for_substring_removal(
	char *param, char *word, int *index, char *format)
{
	t_list		*regexp_list;
	int			ret;

	regexp_list = NULL;
	if ((ret = parse_patterns(word, &regexp_list)) == FAILURE)
		return (ret);
	else if (ret == ERROR)
		return (SUCCESS);
	if (format[0] == '%')
		suffix_pattern_matching(param, index, regexp_list, format);
	else
		prefix_pattern_matching(param, index, regexp_list, format);
	ft_lstdel(&regexp_list, &t_regexp_free);
	return (SUCCESS);
}

/*
** sh_globbing_substring_removal_get_word:
**	Fill word with a malloced string, resulting on performing pattern matching
**	on param, using patterns contained in original word.
**	First it ignore if a '#' in format is here to represent the lenght
**	char, as in a ${#var}.
**	If param is empty word will obviously be empty, because no string can match
**	it (except empty string).
**	It then it looks for the best substring matching patterns in word, using
**	format information on how to select best matching pattern.
**	Finally it fill *word using format and index value filled by previous
**	functions.
**
**	If index is -1, no substring matched, and word shall contain an empty string
**	Else,
**	If in prefix case (#), index contain lenght of substring, starting at
**	index 0.
**	If in suffix case (%), index contain start of subsrting, until end of param.
**
**	Error in parsing result in returning SUCCESS after copied original
**	value of word in *word.
**
**	Returned Values:
**		FAILURE : malloc error
**		SUCCESS : every cases, except malloc error
*/

int			sh_globbing_substring_removal_get_word(
	char *param, char **word, t_expansion *exp, char *format)
{
	int		index;
	int		ret;

	index = -1;
	if (exp->expansion[0] == '#')
		format++;
	if (!*word)
		*word = ft_strstr(exp->expansion, format) + ft_strlen(format);
	if (!param || (*word && !**word))
		return (SUCCESS);
	ret = sh_globbing_for_substring_removal(param, *word, &index, format);
	if (ret == FAILURE)
		return (ret);
	if (*word)
		ft_strdel(word);
	if (ret == ERROR || index == -1)
		*word = ft_strdup("");
	else if (format[0] == '#')
		*word = ft_strndup(param, index);
	else
		*word = ft_strdup(param + index);
	if (!*word)
		return (sh_perror(SH_ERR1_MALLOC, "substring_removal_get_word"));
	return (SUCCESS);
}
