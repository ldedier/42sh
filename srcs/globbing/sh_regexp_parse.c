/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/06 05:44:58 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** check_for_final_slash:
**	If str finish with a '/' character, it add a REG_FINAL_SLASH t_regexp,
**	at the begining of last pattern list of regexp_tab.
**	In verbose mode it show the modified last regexp_list.
**
**	Returned Values:
**		SUCCESS
**		FAILURE : malloc error
*/

static int	check_for_final_slash(char *str, t_list **regexp_tab, int i)
{
	t_regexp	*regexp;
	t_list		*lst;

	if (str[ft_strlen(str) - 1] != '/')
		return (SUCCESS);
	if (!(regexp = malloc(sizeof(*regexp))))
		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (1)"));
	if (!(lst = ft_lstnew(regexp, sizeof(*regexp))))
	{
		free(regexp);
		return (sh_perror(SH_ERR1_MALLOC, "check_for_final_slash (2)"));
	}
	regexp->type = REG_FINAL_SLASH;
	regexp->start = 0;
	regexp->len = 0;
	regexp->value = NULL;
	lst->content = regexp;
	lst->next = regexp_tab[i];
	regexp_tab[i] = lst;
	if (sh_verbose_globbing())
		t_regexp_show_list(regexp_tab[i]);
	return (SUCCESS);
}

static int		sh_regexp_parse_component(char *str, t_list **regexp_list)
{
	int		i;
	int		ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\\' || str[i] == '"')
			ret = sh_regexp_parse_new_string(str, &i, regexp_list);
		else if (str[i] == '[')
			ret = sh_regexp_parse_new_brace(str, &i, regexp_list);
		else if (str[i] == '?')
			ret = sh_regexp_parse_new_quest(&i, regexp_list);
		else if (str[i] == '*')
			ret = sh_regexp_parse_new_star(&i, regexp_list);
		else
			ret = sh_regexp_parse_new_string(str, &i, regexp_list);
		if (ret)
			return (ret);
	}
	if (sh_verbose_globbing())
		t_regexp_show_list(*regexp_list);
	return (SUCCESS);
}

/*
** sh_regexp_parse:
**	Split path given around every '/' char. For every part it create a t_list
**	contaning t_regexp struct. These lists are stored in a t_dy_tab regexp_tab.
**
**	Returned Values :
**		SUCCESS
**		ERROR : Can't parse patterns, globbing shall not be performed
**		FAILURE : malloc error
*/

int		sh_regexp_parse(char *str, t_dy_tab **regexp_tab)
{
	int		i;
	int		ret;
	char	**split;
	t_list	**list_tab;

	i = 0;
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
	check_for_final_slash(str, list_tab, i - 1);
	// leaks on split ??
	ft_strtab_free(split);
	return (ret);
}
