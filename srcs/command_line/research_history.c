/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:38:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 15:38:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_find_in_history(t_command_line *command_line,
			char *to_search_in, char *found)
{
	int			new_len;
	int			len;

	new_len = ft_strlen_utf8(to_search_in);
	command_line->searcher.match_index = found - to_search_in;
	ft_dy_str_cpy_str(command_line->dy_str, to_search_in);
	command_line->nb_chars = new_len;
	len = ft_strnlen_utf8(to_search_in, command_line->searcher.match_index);
	command_line->current_index = command_line->searcher.match_index;
	render_command_line(command_line, len - g_glob.cursor, 1);
	command_line->shell->history.head = command_line->searcher.head;
	return (SUCCESS);
}

int		progress_process_research_history(t_command_line *command_line,
		t_shell *shell)
{
	char		*to_search_in;
	char		*found;

	to_search_in = ((t_entry *)command_line->searcher.head->content)->command;
	if ((found = ft_strstr(&(to_search_in[command_line->searcher.
			match_index + 1]), command_line->searcher.dy_str->str))
				&& ((ft_strcmp(to_search_in, command_line->dy_str->str)
					|| found - to_search_in != command_line->searcher.
							match_index + 1)))
	{
		return (process_find_in_history(command_line,
			to_search_in, found));
	}
	command_line->searcher.match_index = -1;
	if ((command_line->searcher.head = command_line->searcher.head->next)
			== shell->history.commands)
		return (FAILURE);
	else
		return (progress_process_research_history(command_line, shell));
}

int		update_research_history(t_command_line *command_line, t_shell *shell,
			int reset)
{
	command_line->searcher.match_index = -1;
	command_line->searcher.head = shell->history.commands;
	if (reset)
		command_line->searcher.unsuccessful = 0;
	return (process_research_history(command_line, shell));
}

int		process_research_history(t_command_line *command_line, t_shell *shell)
{
	if (command_line->searcher.active)
	{
		if (!command_line->searcher.unsuccessful
				&& ft_strcmp(command_line->searcher.dy_str->str, ""))
		{
			if ((command_line->searcher.unsuccessful =
				progress_process_research_history(command_line, shell)))
				render_command_line(command_line, 0, 1);
		}
		else
			render_command_line(command_line, 0, 1);
	}
	else
	{
		command_line->searcher.unsuccessful = 0;
		command_line->searcher.active = 1;
		ft_bzero(command_line->searcher.dy_str->str,
			command_line->searcher.dy_str->max_size);
		command_line->searcher.match_index = -1;
		render_command_line(command_line, 0, 0);
		command_line->searcher.head = shell->history.commands;
	}
	return (SUCCESS);
}
