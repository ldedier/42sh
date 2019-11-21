/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_vertical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 01:47:21 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:21:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_autocompletion_down(t_shell *shell,
	t_command_line *command_line)
{
	t_file	*file;
	t_file	*prev_file;

	if (!command_line->autocompletion.head)
	{
		command_line->autocompletion.head =
			command_line->autocompletion.choices;
		file = (t_file *)command_line->autocompletion.head->content;
		prev_file = file;
		substitute_command_str(shell, command_line, file->fullname);
		process_autocompletion_switch(command_line, prev_file, file);
		return (SUCCESS);
	}
	prev_file = command_line->autocompletion.head->content;
	command_line->autocompletion.head = command_line->autocompletion.head->next;
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str_from_str(command_line,
		prev_file->fullname, file->fullname);
	process_autocompletion_switch(command_line, prev_file, file);
	return (SUCCESS);
}

int		process_autocompletion_up(t_command_line *command_line)
{
	t_file	*file;
	t_file	*prev_file;

	prev_file = command_line->autocompletion.head->content;
	command_line->autocompletion.head = command_line->autocompletion.head->prev;
	file = (t_file *)command_line->autocompletion.head->content;
	substitute_command_str_from_str(command_line,
		prev_file->fullname, file->fullname);
	process_autocompletion_switch(command_line, prev_file, file);
	return (SUCCESS);
}
