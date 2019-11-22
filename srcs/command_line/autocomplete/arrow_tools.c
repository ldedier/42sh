/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 01:47:50 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:06:27 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	process_autocompletion_switch(t_command_line *command_line,
			t_file *prev_file, t_file *file)
{
	int cl_nb_rows;

	(void)prev_file;
	cl_nb_rows = command_line_nb_rows(command_line);
	if (file->y >= g_glob.winsize.ws_row
		+ command_line->autocompletion.scrolled_lines - (cl_nb_rows)
		|| file->y < command_line->autocompletion.scrolled_lines)
	{
		if (file->y >= g_glob.winsize.ws_row
			+ command_line->autocompletion.scrolled_lines - (cl_nb_rows))
		{
			command_line->autocompletion.scrolled_lines =
				file->y - g_glob.winsize.ws_row + 1 + cl_nb_rows;
		}
		else
		{
			command_line->autocompletion.scrolled_lines = file->y;
		}
	}
	render_command_line(command_line, 0, 1);
}

int		substitute_command_str_from_str(t_command_line *command_line,
			char *from, char *str)
{
	int		len;
	int		utf8_len;
	int		len_to;
	int		utf8_len_to;

	len = ft_strlen(from);
	utf8_len = ft_strlen_utf8(from);
	len_to = ft_strlen(str);
	utf8_len_to = ft_strlen_utf8(str);
	if (ft_substitute_dy_str(command_line->dy_str, str,
		command_line->current_index - len, len))
		return (FAILURE);
	command_line->current_index += len_to - len;
	command_line->nb_chars += utf8_len_to - utf8_len;
	render_command_line(command_line, utf8_len_to - utf8_len, 0);
	return (SUCCESS);
}

int		substitute_command_str(t_shell *shell, t_command_line *command_line,
			char *str)
{
	t_exec	exec;
	int		ret;

	if ((ret = populate_parsed_word_by_index(shell, command_line->dy_str->str,
		command_line->current_index, &exec)))
	{
		if (ret == FAILURE)
			return (sh_free_turn_exec(&exec, FAILURE));
		else
			init_exec(&exec);
	}
	if (process_substitute_command(command_line, str, exec.word, 0))
		return (sh_free_turn_exec_autocompletion(&exec, FAILURE));
	sh_free_turn_exec_autocompletion(&exec, FAILURE);
	return (SUCCESS);
}
