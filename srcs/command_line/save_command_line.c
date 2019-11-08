/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:39:15 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:41:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_update_history(t_command_line *command_line, t_entry *entry)
{
	ft_strdel(&entry->command);
	if (!(entry->command = ft_strdup(command_line->dy_str->str)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_update_history"));
	return (SUCCESS);
}

int			sh_save_command_line(t_command_line *command_line)
{
	t_save	*save;
	t_list	**saves_stack;
	t_entry *entry;

	if (!(save = t_save_new(command_line->dy_str->str,
					command_line->current_index)))
	{
		return (FAILURE);
	}
	saves_stack = get_current_saves_stack(command_line, &entry);
	if ((ft_lstaddnew_ptr(saves_stack, save,
					sizeof(t_save *))))
	{
		t_save_free(save);
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (2)"));
	}
	command_line->edit_counter = 0;
	if (entry && sh_update_history(command_line, entry))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_edit_counter(t_command_line *command_line, int inc)
{
	command_line->edit_counter = ft_max(0, command_line->edit_counter + inc);
	if (command_line->edit_counter >= MAX_EDIT_COUNTER)
		return (sh_save_command_line(command_line));
	return (SUCCESS);
}

int			sh_reset_saves(t_command_line *command_line)
{
	ft_lstdel(&command_line->saves_stack, t_save_free_list);
	if (sh_save_command_line(command_line))
		return (FAILURE);
	return (SUCCESS);
}
