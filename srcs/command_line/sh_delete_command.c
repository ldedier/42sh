/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_delete_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:21:31 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 17:07:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	process_delete_searcher(t_command_line *command_line, t_shell *shell)
{
	int index;
	int len;

	len = ft_strlen(command_line->searcher.dy_str->str);
	index = get_left_w_char_index_dy_str(command_line->searcher.dy_str, len);
	command_line->searcher.dy_str->str[index] = '\0';
	render_command_line(command_line, 0, 0);
	update_research_history(command_line, shell, 1);
}

void	process_process_delete(t_command_line *command_line)
{
	int		left_w_char_index;
	int		diff;

	left_w_char_index = get_left_w_char_index(command_line);
	diff = command_line->current_index - left_w_char_index;
	while (left_w_char_index + diff <= (int)command_line->dy_str->current_size)
	{
		command_line->dy_str->str[left_w_char_index] =
			command_line->dy_str->str[left_w_char_index + diff];
		left_w_char_index++;
	}
	command_line->current_index -= diff;
	command_line->dy_str->current_size -= diff;
	command_line->nb_chars--;
	render_command_line(command_line, -1, 1);
	sh_process_edit_counter(command_line, 1);
}

void	process_delete(t_command_line *command_line, t_shell *shell)
{
	process_cancel_autocompletion(command_line);
	if (command_line->searcher.active)
		process_delete_searcher(command_line, shell);
	else
	{
		if (command_line->current_index == 0)
		{
			ring_bell();
			render_command_line(command_line, 0, 1);
		}
		else
			process_process_delete(command_line);
	}
}

void	process_suppr(t_command_line *command_line)
{
	int diff;
	int i;

	process_cancel_autocompletion(command_line);
	if (command_line->current_index == (int)command_line->dy_str->current_size)
	{
		ring_bell();
		render_command_line(command_line, 0, 1);
	}
	else
	{
		diff = get_right_w_char_index(command_line)
			- command_line->current_index;
		i = command_line->current_index;
		while (i + diff <= (int)command_line->dy_str->current_size)
		{
			command_line->dy_str->str[i] = command_line->dy_str->str[i + diff];
			i++;
		}
		command_line->dy_str->current_size -= diff;
		command_line->nb_chars--;
		render_command_line(command_line, 0, 1);
		sh_process_edit_counter(command_line, 1);
	}
}
