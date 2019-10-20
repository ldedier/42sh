/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 07:35:43 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/20 06:56:25 by jmartel          ###   ########.fr       */
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

static int	sh_pattern_matching_brace_dash(char *name, t_regexp *regexp, int *i, int *j, int not)
{
	char		a;
	char		b;

	a = regexp->value[*j];
	b = regexp->value[*j + 2];
	// ft_dprintf(2, "name : %s |||| a : %c || b : %c || not : %d\n", name + *i, a, b, not);
	if (b < a)
		return (ERROR);
	(*j) += 3;
	while (a <= b)
	{
		if (!not && name[*i] == a)
		{
			// ft_dprintf(2, "match name[i] <> a : %c\n", name[*i], a);
			(*i) += 1;
			return (SUCCESS);
		}
		else if (not && name[*i] == a)
		{
			// ft_dprintf(2, "match excluded char : name[i] <> a : %c\n", name[*i], a);
			return (ERROR);
		}
		a++;
	}
	if (not)
	{
		(*i) += 1;
		return (SUCCESS);
	}
	return (ERROR);
}

static int	sh_pattern_matching_brace(char *name, t_regexp *regexp, int *i)
{
	int		not;
	int		j;

	j = 1;
	while (regexp->value[j] && regexp->value[j] != ']')
	{
		not = 0;
		if (regexp->value[j] == '!' && j++)
			not = 1;
		if (regexp->value[j + 1] == '-' && regexp->value[j + 2])
		{
			if (sh_pattern_matching_brace_dash(name, regexp, i, &j, not) == SUCCESS)
				return (SUCCESS);
		}
		else
		{
			if ((!not && regexp->value[j] == name[*i]) || (not && regexp->value[j] != name[*i]))
			{
				(*i) += 1;
				return (SUCCESS);
			}
		}
		j++;
	}
	return (ERROR);
}

static int	sh_pattern_matching_star(char *name, t_regexp *regexp, int *i, t_list *regexp_head)
{
	t_regexp	*next_regexp;
	char		*buff;
	char		save;

	if (!regexp_head->next)
	{
		while (name[*i])
			(*i) += 1;
		// ft_dprintf(2, "no new regexp : i : %i\n", *i);
		return (SUCCESS);
	}
	next_regexp = (t_regexp*)regexp_head->next->content;
	if (next_regexp->type == REG_STR)
	{
		save = next_regexp->value[next_regexp->len];
		next_regexp->value[next_regexp->len] = '\0';
		// ft_dprintf(2, "looking for %s in : %s\n", next_regexp->value, name + *i);
		if ((buff = ft_strrstr(name + *i, next_regexp->value)))
		{
			next_regexp->value[next_regexp->len] = save;
			(*i) += buff - (name + *i);
			// ft_dprintf(2, "new i : %d (%c)\n", *i, name[*i]);
			return (SUCCESS);
		}
		next_regexp->value[next_regexp->len] = save;
		return (ERROR);
	}
	else if (next_regexp->type == REG_QUEST)
	{
		if (sh_pattern_matching_star(name, regexp, i, regexp_head->next))
			return (ERROR);
		(*i)--;
		return (SUCCESS);
	}
	else if (next_regexp->type == REG_BRACE)
	{
		int		j;
	
		j = ft_strlen(name) - 1;
		// ft_dprintf(2, "i : %d || j : %d\n", *i, j);
		while (j >= (*i) && sh_pattern_matching_brace(name, next_regexp, &j))
		{
			// ft_dprintf(2, "bracket do not feat : %c\n", name[j]);
			j--;
		}
		if (j <= (*i))
			return (ERROR);
		(*i) = j - 1;
		// ft_dprintf(2, "new i : %d || name[i] : %c\n", *i, name[*i]);
		return (SUCCESS);
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
	if (*name == '.' && ((t_regexp*)regexp_head->content)->value[0] != '.')
		return (ERROR);
	// if (regexp_head && regexp_head->next)
	// 	ft_dprintf(2, "processing regexp on %s\n", name + i);
	while (regexp_head && name[i])
	{
		regexp = (t_regexp*)regexp_head->content;
		// ft_dprintf(2, "processing regexp : %s on %s\n", regexp->value, name + i);
		if (regexp->type == REG_STR)
			ret = sh_pattern_matching_str(name, regexp, &i);
		else if (regexp->type == REG_QUEST)
			ret = sh_pattern_matching_quest(name, regexp, &i);
		else if (regexp->type == REG_BRACE)
			ret = sh_pattern_matching_brace(name, regexp, &i);
		else if (regexp->type == REG_STAR)
		{
			ret = sh_pattern_matching_star(name, regexp, &i, regexp_head);
			// if (!ret){ft_dprintf(2, "SUCCESS star\n");}
		}
		else
			return (ERROR);
		if (ret)
			return (ret);
		regexp_head = regexp_head->next;
	}
	while (regexp_head && ((t_regexp*)regexp_head->content)->type == REG_STAR)
		regexp_head = regexp_head->next;
	if (regexp_head || name[i])
		return (ERROR);
	return (SUCCESS);
}
