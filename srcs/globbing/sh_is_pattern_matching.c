/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_pattern_matching.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:30:15 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/26 07:02:14 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** call_pattern_function:
**	Evaluate if name + i can match regexp contained in regexp_head.
**
**	Returned Values
**		SUCCESS : name matched pattern.
**		ERROR : A pattern do not matched
*/

int			sh_globbing_call_pattern_function(
	char *name, int *i, t_list **regexp_head)
{
	int			ret;
	t_regexp	*regexp;

	regexp = (t_regexp*)(*regexp_head)->content;
	if (regexp->type == REG_STR)
		ret = sh_pattern_matching_str(name, regexp, i);
	else if (regexp->type == REG_QUEST)
		ret = sh_pattern_matching_quest(name, regexp, i);
	else if (regexp->type == REG_BRACE)
		ret = sh_pattern_matching_brace(name, regexp, i);
	else if (regexp->type == REG_STAR)
		ret = sh_pattern_matching_star(name, i, *regexp_head);
	else
		ret = ERROR;
	if (ret)
		return (ret);
	if (sh_verbose_globbing())
	{
		ft_dprintf(2, BLUE"\t%s : matched : (", name);
		t_regexp_show(regexp);
		ft_dprintf(2, ")\n"EOC);
	}
	(*regexp_head) = (*regexp_head)->next;
	return (SUCCESS);
}

/*
** sh_is_pattern_matching:
**	Check if name string match all patterns described by t_regexp list.
**
**	Returned Values
**		SUCCESS : Name matched all regexp/
**		ERROR : Name do not matched a regexp.
*/

int			sh_is_pattern_matching(char *name, t_list *regexp_head)
{
	t_regexp	*regexp;
	int			i;

	if (!regexp_head)
		return (SUCCESS);
	i = 0;
	regexp = (t_regexp*)regexp_head->content;
	if (regexp->type == REG_FINAL_SLASH)
		regexp_head = regexp_head->next;
	if (*name == '.' && (regexp->type != REG_STR || regexp->value[0] != '.'))
		return (ERROR);
	while (regexp_head && name[i])
	{
		if (sh_globbing_call_pattern_function(name, &i, &regexp_head))
			return (ERROR);
	}
	while (regexp_head && ((t_regexp*)regexp_head->content)->type == REG_STAR)
		regexp_head = regexp_head->next;
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}

int			sh_is_pattern_matching_for_substring_removal(
	char *name, t_list *regexp_head)
{
	int			i;

	if (!regexp_head)
		return (SUCCESS);
	i = 0;
	while (regexp_head && name[i])
	{
		ft_dprintf(2, "evaluating : %s\n", name);
		if (sh_globbing_call_pattern_function(name, &i, &regexp_head))
			return (ERROR);
	}
	while (regexp_head && ((t_regexp*)regexp_head->content)->type == REG_STAR)
		regexp_head = regexp_head->next;
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}
