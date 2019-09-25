/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_entry.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:33:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 16:33:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_entry		*t_entry_new(int number, char *command)
{
	t_entry *res;

	if (!(res = (t_entry *)malloc(sizeof(t_entry))))
		return (NULL);
	res->number = number;
	res->command = command;
	res->saves_stack = NULL;
	return (res);
}

void		t_entry_free(t_entry *entry)
{
	ft_lstdel_value(&entry->saves_stack);
	free(entry->command);
	free(entry);
}

void		t_entry_print(t_entry *entry, int print_number)
{
	if (print_number)
		ft_printf("%d\t%s\t\t(%p)\n", entry->number, entry->command, entry);
	else
		ft_printf("\t%s\n", entry->command);
}