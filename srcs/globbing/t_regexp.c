/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_regexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:26:35 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/20 08:46:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_regexp		*t_regexp_new_push(t_list **regexp_list)
{
	t_regexp	*regexp;
	t_list		*lst;

	if (!(regexp = malloc(sizeof(*regexp))))
		return (sh_perrorn(SH_ERR1_MALLOC, "t_regexp_new_push (1)"));
	if (!(lst = ft_lstnew(regexp, sizeof(*regexp))))
	{
		free(regexp);
		return (sh_perrorn(SH_ERR1_MALLOC, "t_regexp_new_push (2)"));
	}
	ft_lstadd_last(regexp_list, lst);
	return (regexp);
}

void			t_regexp_show_list(t_list *head)
{
	if (!head)
		ft_dprintf(2, "\n"EOC);
	while (head)
	{
		t_regexp_show((t_regexp*)head->content);
		head = head->next;
		if (head)
			ft_dprintf(2, " || ");
		else
			ft_dprintf(2, "\n"EOC);
	}
}

void			t_regexp_show(t_regexp *regexp)
{
	if (regexp->type == REG_STAR)
		ft_dprintf(2, "REG_STAR");
	else if (regexp->type == REG_STR)
		ft_dprintf(2, "REG_STR : %s", regexp->value);
	else if (regexp->type == REG_QUEST)
		ft_dprintf(2, "REG_QUEST");
	else if (regexp->type == REG_BRACE)
		ft_dprintf(2, "REG_BRACE : %s", regexp->value);
	else if (regexp->type == REG_FINAL_SLASH)
		ft_dprintf(2, "REG_FINAL_SLASH");
}

void			t_regexp_free(void *ptr, size_t size)
{
	t_regexp	*regexp;

	regexp = (t_regexp*)ptr;
	if (regexp->value)
		free(regexp->value);
	free(regexp);
	(void)size;
}

void			t_regexp_free_tab(t_dy_tab **regexp_tab)
{
	int			i;
	t_list		**list_tab;

	i = 0;
	list_tab = (t_list**)(*regexp_tab)->tbl;
	while (list_tab[i])
	{
		ft_lstdel(list_tab + i, &t_regexp_free);
		i++;
	}
	ft_dy_tab_del_ptr(*regexp_tab);
	*regexp_tab = NULL;
}
