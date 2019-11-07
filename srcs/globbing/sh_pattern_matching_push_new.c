/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pattern_matching_push_new.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:26:28 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/07 05:31:59 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void	pattern_matching_push_find_place(
	t_list **head, t_list **prev, char *filename)
{
	while (*head)
	{
		if (ft_strcmp((char*)(*head)->content, filename) > 0)
			return ;
		(*prev) = *head;
		(*head) = (*head)->next;
	}
	return ;
}

static void	pattern_matching_push(t_list **matches, t_list *new)
{
	t_list	*head;
	t_list	*prev;

	if (!*matches)
	{
		*matches = new;
		return ;
	}
	head = *matches;
	prev = NULL;
	pattern_matching_push_find_place(&head, &prev, (char*)new->content);
	if (prev == NULL)
	{
		new->next = head;
		*matches = new;
	}
	else if (head == NULL)
		prev->next = new;
	else
	{
		prev->next = new;
		new->next = head;
	}
}

/*
** pattern_matching_push_new:
**	Create a new t_list to store previously allocated path string. Then it
**	push it into list designated by *matches, sorting it's component using
**	ascii order.
**
**	FAILURE : malloc error
**	SUCCESS : else
*/

int			pattern_matching_push_new(t_list **matches, char *path)
{
	t_list	*new;

	if (!(new = ft_lstnew(path, ft_strlen(path) + 1)))
	{
		free(path);
		return (FAILURE);
	}
	pattern_matching_push(matches, new);
	return (SUCCESS);
}
