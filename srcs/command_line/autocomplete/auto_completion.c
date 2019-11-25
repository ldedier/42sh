/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 23:28:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 10:20:26 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			process_advanced_completion(
	t_command_line *command_line, t_word word)
{
	t_file *file;

	if (command_line->autocompletion.head)
		command_line->autocompletion.head =
			command_line->autocompletion.head->next;
	else
		command_line->autocompletion.head =
			command_line->autocompletion.choices;
	file = (t_file *)command_line->autocompletion.head->content;
	if (process_substitute_command(command_line, file->fullname, word, 1))
		return (FAILURE);
	return (SUCCESS);
}

int			process_completion_expand(t_command_line *command_line,
		char *str, t_word word)
{
	if (ft_dlstlength(command_line->autocompletion.choices) == 1)
	{
		if (process_substitute_command(command_line, str, word, 1))
			return (FAILURE);
	}
	else
	{
		command_line->autocompletion.active = 1;
		if (process_substitute_command(command_line, str, word, 1))
			return (FAILURE);
	}
	return (SUCCESS);
}

int			process_completion(
	t_command_line *command_line, t_word word)
{
	char	*str;

	if (!(str = get_completion_str(command_line)))
		return (1);
	if (!ft_strcmp("", word.str) || (!ft_strcmp(word.str, str)
				&& word.start_index + word.len == command_line->current_index))
	{
		if (process_completion_expand(command_line, str, word) == FAILURE)
			return (ft_free_turn(str, FAILURE));
	}
	else
	{
		if (process_substitute_command(command_line, str, word, 1))
			return (ft_free_turn(str, 1));
	}
	return (ft_free_turn(str, 0));
}

static int	process_tab_autocompletion(
	t_shell *shell, t_command_line *command_line)
{
	int		ret;
	t_exec	exec;

	if ((ret = populate_parsed_word_by_index(shell,
		command_line->dy_str->str, command_line->current_index, &exec)))
	{
		if (ret == FAILURE)
			return (sh_free_turn_exec_autocompletion(&exec, FAILURE));
		else if (!exec.word.str)
			return (SUCCESS);
		else
			init_exec_autocompletion(&exec);
	}
	ft_dlstdel(&command_line->autocompletion.choices, &free_file_dlst);
	if (populate_choices_from_word(command_line, shell, &exec.word))
		return (sh_free_turn_exec_autocompletion(&exec, 1));
	if (command_line->autocompletion.choices != NULL)
		ret = process_completion(command_line, exec.word);
	sh_free_turn_exec_autocompletion(&exec, ret == FAILURE);
	return (ret);
}

int			process_tab(t_shell *shell, t_command_line *command_line)
{
	command_line->autocompletion.choices_common_len = -1;
	if (!command_line->autocompletion.active)
		return (process_tab_autocompletion(shell, command_line));
	process_autocompletion_down(shell, command_line);
	return (SUCCESS);
}
