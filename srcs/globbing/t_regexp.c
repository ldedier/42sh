/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_regexp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 23:26:35 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/21 05:30:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_regexp		*t_regexp_new_push(t_list **regexp_list)
{
	t_regexp	*regexp;
	t_list		*lst;

	if (!(regexp = malloc(sizeof(*regexp))))
		return (NULL); //perrror
	if (!(lst = ft_lstnew(regexp, sizeof(*regexp))))
	{
		free(regexp);
		return (NULL); //perrror
	}
	ft_lstadd_last(regexp_list, lst);
	return (regexp);
}

void			t_regexp_show_list(t_list *head)
{
	while (head)
	{
		t_regexp_show((t_regexp*)head->content);
		head = head->next;
		if (head)
			ft_dprintf(2, BLUE" || " EOC);
		else
			ft_dprintf(2, "\n");
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
}

void		t_regexp_free(void *ptr, size_t size)
{
	t_regexp	*regexp;

	regexp = (t_regexp*)ptr;
	if (regexp->value)
		free(regexp->value);
	free(regexp);
	(void)size;
}
