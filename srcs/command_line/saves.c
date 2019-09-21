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

int			sh_save_command_line(t_command_line *command_line)
{
	char *command_line_dup;

	if (!(command_line_dup = (char *)malloc(sizeof(char)
		* (command_line->dy_str->current_size + 1))))
	{
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (1)"));
	}
	ft_memcpy(command_line_dup, command_line->dy_str->str,
			command_line->dy_str->current_size);
	command_line_dup[command_line->dy_str->current_size] = 0;
	if ((ft_lstaddnew_ptr(&command_line->saves_stack, command_line_dup,
		sizeof(char *))))
	{
		return (sh_perror(SH_ERR1_MALLOC, "save_command_line (2)"));
	}
	command_line->edit_counter = 0;
	return (SUCCESS);
}

int			sh_restore_save(t_command_line *command_line)
{
	char *save;

	if ((save = ft_lstpop_ptr(&command_line->saves_stack)))
	{
		if (switch_command_line(command_line, save))
		{
			free(save);
			return (FAILURE);
		}
		free(save);
	}
 	return (SUCCESS);
}

int			sh_process_edit_counter(t_command_line *command_line, int inc)
{
	command_line->edit_counter = ft_max(0, command_line->edit_counter + inc);
	if (command_line->edit_counter > MAX_EDIT_COUNTER)
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
