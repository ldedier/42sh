/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_is_pattern_matching.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:30:15 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/07 01:42:09 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_is_pattern_matching:
**	Check if name string match pattern described by regexp_head t_regexp list.
**
**
**	Returned Values
**		SUCCESS : Name match regexp
**		ERROR : Name do not match regexp
// Can return failure ??
**		FAILURE : 
*/

int			sh_is_pattern_matching(char *name, t_list *regexp_head)
{
	t_regexp	*regexp;
	int			i;
	int			ret;

	if (!regexp_head)
		return (SUCCESS); // is it used ?
	i = 0;
	ret = SUCCESS;
	regexp = (t_regexp*)regexp_head->content;
	if (regexp->type == REG_FINAL_SLASH)
		regexp_head = regexp_head->next;
	if (*name == '.' && (regexp->type != REG_STR || regexp->value[0] != '.'))
		return (ERROR);
	while (regexp_head && name[i])
	{
		regexp = (t_regexp*)regexp_head->content;
		if (regexp->type == REG_STR)
			ret = sh_pattern_matching_str(name, regexp, &i);
		else if (regexp->type == REG_QUEST)
			ret = sh_pattern_matching_quest(name, regexp, &i);
		else if (regexp->type == REG_BRACE)
			ret = sh_pattern_matching_brace(name, regexp, &i);
		else if (regexp->type == REG_STAR)
			ret = sh_pattern_matching_star(name, regexp, &i, regexp_head);
		if (ret)
			return (ret);
		if (sh_verbose_globbing())
			{ft_dprintf(2, BLUE"\t%s : matched : (", name); t_regexp_show(regexp);ft_dprintf(2, ")\n"EOC);}
		regexp_head = regexp_head->next;
	}
	while (regexp_head && ((t_regexp*)regexp_head->content)->type == REG_STAR)
		regexp_head = regexp_head->next;
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}
