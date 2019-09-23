/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:22:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/21 18:22:48 by ldedier          ###   ########.fr       */
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

t_list		**get_current_saves_stack(t_command_line *command_line,
	t_entry **entry)
{
	t_list **res;
	t_shell *shell;

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

int			sh_save_command_line(t_command_line *command_line)
{
	char	*command_line_dup;
	t_list	**saves_stack;
	t_entry *entry;

	if (!(command_line_dup = (char *)malloc(sizeof(char)
		* (command_line->dy_str->current_size + 1))))
	{
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (1)"));
	}
	ft_memcpy(command_line_dup, command_line->dy_str->str,
			command_line->dy_str->current_size);
	command_line_dup[command_line->dy_str->current_size] = 0;
	saves_stack = get_current_saves_stack(command_line, &entry);
	if ((ft_lstaddnew_ptr(saves_stack, command_line_dup,
		sizeof(char *))))
	{
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (2)"));
	}
	command_line->edit_counter = 0;
	if (entry && sh_update_history(command_line, entry))
		return (FAILURE);
	return (SUCCESS);
}

int			process_restore_save(t_command_line *command_line,
				char *save, int *ret)
{
	if (ft_strcmp(command_line->dy_str->str, save))
	{
		if (switch_command_line(command_line, save) != SUCCESS)
			*ret = FAILURE;
		else
			*ret = SUCCESS;
		return (1);
	}
	else
	{
		*ret = SUCCESS;
		return (0);
	}
}

int			sh_restore_save(t_command_line *command_line)
{
	char		*save;
	t_entry		*entry;
	t_list		**saves_stack;
	int			ret;

	saves_stack = get_current_saves_stack(command_line, &entry);
	while (*saves_stack && (*saves_stack)->next
		&& (save = ft_lstpop_ptr(saves_stack)))
	{
		if (process_restore_save(command_line, save, &ret))
		{
			free(save);
			return (ret);
		}
		free(save);
	}
	save = (*saves_stack)->content;
	process_restore_save(command_line, save, &ret);
	return (ret);
}

int			sh_restore_all_save(t_command_line *command_line)
{
	char		*save;
	t_entry		*entry;
	t_list		**saves_stack;
	int			ret;

	saves_stack = get_current_saves_stack(command_line, &entry);
	while (saves_stack && (*saves_stack)->next
		&& (save = ft_lstpop_ptr(saves_stack)))
	{
		free(save);
	}
	save = (*saves_stack)->content;
	process_restore_save(command_line, save, &ret);
	return (ret);
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
	ft_lstdel_value(&command_line->saves_stack);
	if (sh_save_command_line(command_line))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_init_entry_saves(t_entry *entry)
{
	char	*cmd_dup;

	if (entry->saves_stack == NULL)
	{
		if (!(cmd_dup = ft_strdup(entry->command)))
			return (sh_perror(SH_ERR1_MALLOC, "sh_generate_entry_save (1)"));
		if (ft_lstaddnew_ptr(&entry->saves_stack, cmd_dup, sizeof(char *)))
		{
			free(cmd_dup);
			return (sh_perror(SH_ERR1_MALLOC, "sh_generate_entry_save (2)"));
		}
	}
	return (SUCCESS);
}

