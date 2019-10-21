/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 01:38:22 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int		sh_regexp_parse_new_string(char *str, int *i, t_list **regexp_list)
{
	int			start;
	t_regexp	*regexp;
	char		quoted;

	start = *i;
	if (str[*i] == '[')
		(*i) += 1;
	quoted = 0;
	while (str[*i])
	{
		ft_dprintf(2, "while : str[*i] : %c (%d) || quoted L: %c\n", str[*i], *i, quoted);
		if (str[*i] == '\'' || str[*i] == '\\' || str[*i] == '"')
		{
			quoted = str[*i];
			(*i) += 1;
		}
		else if (quoted == '\'' || quoted == '"')
		{
			while (str[*i] && str[*i] != quoted)
				(*i) += 1;
			if (str[*i])
				(*i) += 1;
			quoted = 0;
		}
		else if (quoted == '\\')
		{
			(*i) += 1;
			quoted = 0;
		}
		else if (str[*i] == '?' || str[*i] == '[' || str[*i] == '*')
			break ;
		else
			(*i) += 1;
	}
	if (quoted)
	{
		ft_dprintf(2, "returning ERROR in parsing str\n" );
		return (ERROR); // Is it pertinent ?
	}
	ft_dprintf(2, "str[*i] : %c (%d)\n", str[*i], *i);
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (FAILURE);
	regexp->type = REG_STR;
	regexp->start = start;
	regexp->len = *i - start;
	regexp->value = str + start;
	return (SUCCESS);
}

static int		sh_regexp_parse_new_bracket(char *str, int *i, t_list **regexp_list)
{
	int			start;
	t_regexp	*regexp;

	start = *i;
	while (str[*i] && str[*i] != ']')
		(*i)++;
	if (!str[*i])
	{
		*i = start;
		return (sh_regexp_parse_new_string(str, i, regexp_list));
	}
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (FAILURE);
	regexp->type = REG_BRACE;
	regexp->start = start;
	regexp->len = *i - start + 1;
	regexp->value = str + start;
	(*i)++;
	return (SUCCESS);
}

static int		sh_regexp_parse_new_question(char *str, int *i, t_list **regexp_list)
{
	int			start;
	t_regexp	*regexp;

	start = (*i);
	(*i)++;
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (FAILURE);
	regexp->type = REG_QUEST;
	regexp->start = start;
	regexp->len = 1;
	regexp->value = str + start;
	return (SUCCESS);
}

static int		sh_regexp_parse_new_star(char *str, int *i, t_list **regexp_list)
{
	int			start;
	t_regexp	*regexp;

	start = (*i);
	(*i)++;
	if (!(regexp = t_regexp_new_push(regexp_list)))
		return (FAILURE);
	regexp->type = REG_STAR;
	regexp->start = start;
	regexp->len = 1;
	regexp->value = str + start;
	return (SUCCESS);
}

static int		sh_regexp_parse_component(char *str, t_list **regexp_list)
{
	int		i;
	int		ret;

	i = 0;
	// ft_dprintf(2, "regexp_parse_component : %s\n", str);
	while (str[i])
	{
		if (sh_verbose_globbing())
			ft_dprintf(2, GREEN"new loop : on %c (%d)\n"EOC, str[i], i);
		if (str[i] == '\'' || str[i] == '\\' || str[i] == '"')
			ret = sh_regexp_parse_new_string(str, &i, regexp_list);
		else if (str[i] == '[')
			ret = sh_regexp_parse_new_bracket(str, &i, regexp_list);
		else if (str[i] == '?')
			ret = sh_regexp_parse_new_question(str, &i, regexp_list);
		else if (str[i] == '*')
			ret = sh_regexp_parse_new_star(str, &i, regexp_list);
		else
			ret = sh_regexp_parse_new_string(str, &i, regexp_list);
		if (ret)
			return (ret);
	}
	if (sh_verbose_globbing())
		t_regexp_show_list(*regexp_list);
	return (SUCCESS);
}

int		sh_regexp_parse(char *str, t_dy_tab **regexp_tab)
{
	int		i;
	int		ret;
	char	**split;
	t_list	**list_tab;

	i = 0;
	if (!ft_strpbrk(str, "?[*"))
		return (SUCCESS);
	if (*str == '.' && *str == '/')
		str += 2;
	else if (*str == '/')
		str++;
	if (!(split = ft_strsplit(str, '/')))
		return (FAILURE); // perror
	if (!(*regexp_tab = ft_dy_tab_new(ft_strtab_len(split) + 1)))
	{
		ft_strtab_free(split);
		return (FAILURE); // perror
	}
	list_tab = (t_list**)(*regexp_tab)->tbl;
	ret = SUCCESS;
	while (split[i] && !ret)
	{
		ft_dy_tab_add_ptr(*regexp_tab, NULL);
		list_tab[i] = NULL;
		ret = sh_regexp_parse_component(split[i], &(list_tab[i]));
		i++;
	}
	// leaks on split
	// ft_strtab_free(split);
	return (ret);
}
