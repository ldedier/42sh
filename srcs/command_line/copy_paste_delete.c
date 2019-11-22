/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:56:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/07 15:23:24 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		command_line_copy_all(t_command_line *command_line)
{
	if (command_line->clipboard != NULL)
		free(command_line->clipboard);
	if (!(command_line->clipboard = ft_strndup(command_line->dy_str->str,
		MAX_YANK)))
		return (sh_perror(SH_ERR1_MALLOC, "command_line_copy_all"));
	return (SUCCESS);
}

int		copy_selection_to_clipboard(t_command_line *command_line)
{
	int n;
	int index;

	if (command_line->clipboard != NULL)
		free(command_line->clipboard);
	n = ft_abs(command_line->current_index - command_line->pinned_index);
	index = ft_min(command_line->current_index, command_line->pinned_index);
	if (!(command_line->clipboard =
			ft_strndup(&command_line->dy_str->str[index], ft_min(n, MAX_YANK))))
		return (sh_perror(SH_ERR1_MALLOC, "copy_selection_to_clipboard"));
	return (SUCCESS);
}

int		paste_current_index(t_command_line *command_line, char *to_paste)
{
	int utf8_len;
	int len;

	if (!to_paste)
		return (SUCCESS);
	len = ft_strlen(to_paste);
	utf8_len = ft_nb_columns(to_paste);
	if (ft_substitute_dy_str(command_line->dy_str, to_paste,
			command_line->current_index, 0))
		return (sh_perror(SH_ERR1_MALLOC, "paste_current_index"));
	command_line->current_index += len;
	command_line->nb_chars += utf8_len;
	render_command_line(command_line, utf8_len, 1);
	return (SUCCESS);
}

int		delete_command_line_selection(t_command_line *command_line)
{
	int min;
	int max;
	int len;
	int utf8_len;

	populate_min_max_selection(command_line, &min, &max);
	len = max - min;
	utf8_len = ft_strnlen_utf8(&command_line->dy_str->str[min], len);
	if (ft_substitute_dy_str(command_line->dy_str, "", min, len))
		return (sh_perror(SH_ERR1_MALLOC, "delete_command_line_selection"));
	command_line->nb_chars -= utf8_len;
	if (command_line->current_index == min)
		render_command_line(command_line, 0, 1);
	else
	{
		command_line->current_index -= len;
		render_command_line(command_line, -utf8_len, 1);
	}
	return (SUCCESS);
}
