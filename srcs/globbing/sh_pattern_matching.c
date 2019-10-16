/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 07:35:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/16 08:17:31 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_pattern_matching_str(char *name, t_regexp *regexp, int *i)
{
	if (ft_strnequ(regexp->value, name + *i, regexp->len))
		(*i) += regexp->len;
	else
		return (ERROR);
	return (SUCCESS);
}

static int	sh_pattern_matching_quest(char *name, t_regexp *regexp, int *i)
{
	if (name[*i])
		(*i) += regexp->len;
	else
		return (ERROR);
	return (SUCCESS);
}

static int	sh_pattern_matching_brace_dash(char *name, t_regexp *regexp, int *i, int *j)
{
	char		a;
	char		b;

	a = regexp->value[*j];
	b = regexp->value[*j + 2];
	ft_dprintf(2, "name : %s |||| a : %c || b : %c\n", name + *i, a, b);
	if (b < a)
		return (ERROR);
	(*j) += 3;
	while (a <= b)
	{
		if (name[*i] == a)
		{
			ft_dprintf(2, "match !! name[i] <> a : %c\n", name[*i], a);
			(*i) += 1;
			return (SUCCESS);
		}
		a++;
	}
	return (ERROR);
}

static int	sh_pattern_matching_brace(char *name, t_regexp *regexp, int *i)
{
	int		not;
	int		j;

	j = 1;
	not = 0;
	if (*regexp->value == '!')
	{
		not = 1;
		j++;
	}
	while (regexp->value[j] && regexp->value[j] != ']')
	{
		if (regexp->value[j + 1] == '-' && regexp->value[j + 2])
		{
			if (sh_pattern_matching_brace_dash(name, regexp, i, &j) == SUCCESS)
				return (SUCCESS);
		}
		else
		{
			if (regexp->value[j] == name[*i])
			{
				(*i) += 1;
				return (SUCCESS);
			}
		}
		j++;
	}
		return (ERROR);
}

int			sh_is_pattern_matching(char *name, t_list *regexp_head)
{
	t_regexp	*regexp;
	int			i;
	int			ret;

	i = 0;
	ret = SUCCESS;
	while (regexp_head && name[i])
	{
		regexp = (t_regexp*)regexp_head->content;
		if (regexp->type == REG_STR)
			ret = sh_pattern_matching_str(name, regexp, &i);
		else if (regexp->type == REG_QUEST)
			ret = sh_pattern_matching_quest(name, regexp, &i);
		else if (regexp->type == REG_BRACE)
			ret = sh_pattern_matching_brace(name, regexp, &i);
		else
			return (ERROR);
		if (ret)
			return (ret);
		regexp_head = regexp_head->next;
	}
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}
