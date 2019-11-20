/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_regexp_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:53:16 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 10:13:00 by jmartel          ###   ########.fr       */
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
	regexp->len = 0;
	regexp->value = NULL;
	lst->content = regexp;
	lst->next = regexp_tab[i];
	regexp_tab[i] = lst;
	if (sh_verbose_globbing())
		t_regexp_show_list(regexp_tab[i]);
	return (SUCCESS);
}

/*
** sh_regexp_parse_path_component:
**	Parse part of the a path and try to create regexp_patterns.
**
**	Returned Values
**		SUCCESS
**		ERROR : Error in parsing a component that shall cancel globbing process
**		FAILURE : Malloc error
*/

int			sh_regexp_parse_path_component(char *str, t_list **regexp_list)
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
	{
		dprintf(2, GREEN"\tparsed : %s => ", str);
		t_regexp_show_list(*regexp_list);
	}
	return (SUCCESS);
}

/*
** init_split_table:
**	Parse str string, to fill a split table, corresping to a path splitted
**	around '/' characters.
**	Function is ignoring any prefix in "./" and '/'.
**
**	Returned Values
**		SUCCESS : Successfully field split table
**		FAILURE : Malloc error
*/

static int	init_dy_tab_regexp(char *str, t_dy_tab **regexp_tab)
{
	char	*path;
	int		len;

	len = 0;
	while ((path = ft_strsep(&str, "/")))
		len++;
	if (!(*regexp_tab = ft_dy_tab_new(len + 1)))
		return (sh_perror(SH_ERR1_MALLOC, "init_split_table (2)"));
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

int			sh_regexp_parse(char *str, t_dy_tab **regexp_tab, t_dy_tab *quotes)
{
	int		i;
	int		ret;
	char	*path;
	t_list	**list_tab;

	return (sh_glob_lexer(str, regexp_tab, quotes));

	
	if (init_dy_tab_regexp(str, regexp_tab) == FAILURE)
		return (FAILURE);
	list_tab = (t_list**)(*regexp_tab)->tbl;
	i = 0;
	ret = SUCCESS;
	while ((path = ft_strsep(&str, "/")) && !ret)
	{
		if (!*path)
			continue ;
		ft_dy_tab_add_ptr(*regexp_tab, NULL); // check ret value : true if error
		list_tab[i] = NULL;
		ret = sh_regexp_parse_path_component(path, &(list_tab[i]));
		i++;
	}
	ft_strsep(NULL, NULL);
	check_for_final_slash(str, list_tab, i - 1);
	if (ret)
		t_regexp_free_tab(regexp_tab);
	return (ret);
	(void)quotes;//
}
