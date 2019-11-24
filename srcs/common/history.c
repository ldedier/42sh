/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:37:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 16:11:33 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void			print_history(t_history *history)
{
	t_dlist *ptr;
	int		first;
	t_entry	*entry;

	if (!history->commands)
		return ;
	ptr = history->commands->prev;
	first = 1;
	while ((ptr != history->commands->prev && ptr != NULL)
		|| (first && ptr != NULL))
	{
		entry = (t_entry *)ptr->content;
		t_entry_print(entry, 1);
		ptr = ptr->prev;
		first = 0;
	}
}

static int		sh_too_big_to_append_to_history(char *command)
{
	int i;

	i = 0;
	while (command[i] && i < MAX_LEN_HISTORY_ENTRY)
		i++;
	return (command[i]);
}

static void		sh_append_entry_wrap(t_history *history, char *command)
{
	t_entry *entry;

	history->commands = history->commands->prev;
	entry = history->commands->content;
	ft_strdel(&entry->command);
	entry->command = command;
	history->to = entry->number;
	history->from = ((t_entry *)history->commands->prev->content)->number;
}

static int		sh_append_entry(t_history *history, char *command)
{
	t_entry *entry;

	if (history->nb_entries <= ft_max(32767, HISTSIZE))
	{
		history->from = 1;
		history->to = ++history->nb_entries;
		if (!(entry = t_entry_new(history->to, command)))
		{
			free(command);
			return (sh_perror(SH_ERR1_MALLOC, "sh_append_entry (1)"));
		}
		if (ft_add_to_dlist_ptr(&history->commands, entry, sizeof(entry)))
		{
			t_entry_free(entry);
			return (sh_perror(SH_ERR1_MALLOC, "sh_append_entry (2)"));
		}
	}
	else
		sh_append_entry_wrap(history, command);
	history->head_start.next = history->commands;
	return (SUCCESS);
}

int				sh_append_to_history(t_history *history, char *command,
	int append_file)
{
	int		fd;
	char	*str;

	if (sh_too_big_to_append_to_history(command) || !ft_strcmp(command, "")
		|| (history->commands
			&& !ft_strcmp((char *)history->commands->content, command)))
		return (SUCCESS);
	if (!(str = ft_strdup(command)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_append_to_history (1)"));
	if (sh_append_entry(history, str) != SUCCESS)
		return (FAILURE);
	if (append_file)
	{
		if ((fd = open(PATH"/"HISTORY_FILE,
				O_WRONLY | O_CREAT | O_APPEND | O_NOFOLLOW, S_IRWXU)) == -1)
			return (sh_perror(SH_ERR1_HISTORY, "sh_append_to_history (3)"));
		ft_dprintf(fd, "%s\n", command);
		close(fd);
	}
	return (SUCCESS);
}
