/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:22:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:41:52 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_list		**get_current_saves_stack(t_command_line *command_line,
	t_entry **entry)
{
	t_list	**res;
	t_shell	*shell;

	shell = command_line->shell;
	*entry = NULL;
	if (command_line->shell->history.head
		&& command_line->shell->history.head != &shell->history.head_start)
	{
		*entry = command_line->shell->history.head->content;
		res = &(*entry)->saves_stack;
	}
	else
		res = &command_line->saves_stack;
	return (res);
}

int			sh_init_entry_saves(t_entry *entry)
{
	t_save	*save;

	if (entry->saves_stack == NULL)
	{
		if (!(save = t_save_new(entry->command, ft_strlen(entry->command))))
			return (FAILURE);
		if (ft_lstaddnew_ptr(&entry->saves_stack, save, sizeof(t_save *)))
		{
			t_save_free(save);
			return (sh_perror(SH_ERR1_MALLOC, "sh_generate_entry_save"));
		}
	}
	return (SUCCESS);
}
