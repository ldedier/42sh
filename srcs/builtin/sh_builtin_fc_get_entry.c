/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_get_entry.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 04:49:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 19:40:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_dlist		*get_entry_from_positive_number(t_history *history,
		int number)
{
	int		first;
	t_entry	*entry;
	t_dlist	*ptr;

	if (!history->nb_entries)
		return (NULL);
	else if (number > history->nb_entries)
		return (history->commands);
	else
	{
		ptr = history->commands;
		first = 1;
		while ((ptr != history->commands && ptr != NULL)
			|| (first && ptr != NULL))
		{
			entry = (t_entry *)ptr->content;
			if (entry->number == number)
				return (ptr);
			ptr = ptr->next;
			first = 0;
		}
		return (NULL);
	}
}

static t_dlist		*get_entry_from_number(t_history *history, int number)
{
	t_dlist	*ptr;
	int		i;

	i = 0;
	if (number <= 0)
	{
		i = -1;
		ptr = history->commands;
		while (i > number && ptr != history->commands->prev)
		{
			ptr = ptr->next;
			i--;
		}
		return (ptr);
	}
	else
		return (get_entry_from_positive_number(history, number));
	return (NULL);
}

static t_dlist		*get_entry_from_substring(t_history *history, char *str)
{
	t_dlist *ptr;
	int		first;
	t_entry *entry;

	ptr = history->commands;
	first = 1;
	while ((ptr != history->commands || first) && ptr != NULL)
	{
		entry = (t_entry *)ptr->content;
		if (!ft_strncmp(entry->command, str, ft_strlen(str)))
			return (ptr);
		first = 0;
		ptr = ptr->next;
	}
	return (NULL);
}

t_dlist				*get_entry_from_fc_operand(t_history *history,
						t_fc_operand *op)
{
	if (!history->nb_entries)
		return (NULL);
	if (op->type == E_FC_STRING)
		return (get_entry_from_substring(history, op->un.string));
	else
		return (get_entry_from_number(history, op->un.integer));
}
