/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:34:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 21:37:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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
