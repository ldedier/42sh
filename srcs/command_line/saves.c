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

t_save		*t_save_new(char *str, int index)
{
	t_save *res;

	if (!(res = malloc(sizeof(t_save))))
		return (sh_perrorn(SH_ERR1_MALLOC, "t_save_new (1)"));
	res->current_index = index;
	if (!(res->str = ft_strdup(str)))
	{
		free(res);
		return (sh_perrorn(SH_ERR1_MALLOC, "t_save_new (2)"));
	}
	return (res);
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
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (2)"));
	}
	command_line->edit_counter = 0;
	if (entry && sh_update_history(command_line, entry))
		return (FAILURE);
	return (SUCCESS);
}

int			process_restore_save(t_command_line *command_line,
				t_save *save, int *ret)
{

	if (ft_strcmp(command_line->dy_str->str, save->str))
	{
		if (command_line->edit_style == E_EDIT_STYLE_READLINE)
			*ret = switch_command_line_index(command_line,
					save->str, save->current_index);
		else
			*ret = switch_command_line(command_line, save->str, 0);
		return (1);
	}
	else
	{
		*ret = SUCCESS;
		return (0);
	}
}

void		t_save_free(t_save *save)
{
	free(save->str);
	free(save);
}

void		t_save_free_list(void *s, size_t dummy)
{
	t_save *save;

	(void)dummy;
	save = (t_save *)s;
	t_save_free(save);
}

int			sh_restore_save(t_command_line *command_line)
{
	t_save		*save;
	t_entry		*entry;
	t_list		**saves_stack;
	int			ret;

	saves_stack = get_current_saves_stack(command_line, &entry);
	while (*saves_stack && (*saves_stack)->next
		&& (save = ft_lstpop_ptr(saves_stack)))
	{
		if (process_restore_save(command_line, save, &ret))
		{
			t_save_free(save);
			return (ret);
		}
		t_save_free(save);
	}
	save = (*saves_stack)->content;
	process_restore_save(command_line, save, &ret);
	return (ret);
}

int			sh_restore_all_save(t_command_line *command_line)
{
	t_save		*save;
	t_entry		*entry;
	t_list		**saves_stack;
	int			ret;

	saves_stack = get_current_saves_stack(command_line, &entry);
	while (saves_stack && (*saves_stack)->next
		&& (save = ft_lstpop_ptr(saves_stack)))
	{
		t_save_free(save);
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
	ft_lstdel(&command_line->saves_stack, t_save_free_list);
	if (sh_save_command_line(command_line))
		return (FAILURE);
	return (SUCCESS);
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

