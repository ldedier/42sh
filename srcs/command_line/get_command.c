/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:31:34 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/05 15:37:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_add_to_dy_str(t_dy_str *dy_str,
			unsigned char buffer[READ_BUFF_SIZE], int nb_bytes)
{
	char buffer2[READ_BUFF_SIZE + 1];

	ft_memcpy(buffer2, buffer, nb_bytes);
	buffer2[nb_bytes] = 0;
	if (ft_substitute_dy_str(dy_str, buffer2, ft_strlen(dy_str->str), 0))
		return (sh_perror(SH_ERR1_MALLOC, "sh_add_to_dy_str"));
	return (SUCCESS);
}

int		sh_add_to_command(t_command_line *command_line,
		unsigned char buffer[READ_BUFF_SIZE], int nb_bytes)
{
	int i;

	i = 0;
	while (i < nb_bytes)
	{
		if (ft_dy_str_add_index(command_line->dy_str, (char)buffer[i],
				command_line->current_index++))
			return (1);
		i++;
	}
	command_line->nb_chars++;
	return (0);
}

int		reset_command_line(t_shell *shell, t_command_line *command_line)
{
	shell->history.head = &shell->history.head_start;
	command_line->autocompletion.head = NULL;
	g_glob.cursor = 0;
	flush_command_line(command_line);
	if (update_prompt(shell, command_line) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		sh_get_command(t_shell *shell, t_command_line *command_line)
{
	sh_add_eof(command_line->interrupted);
	command_line->interrupted = 0;
	if (reset_command_line(shell, command_line) == FAILURE)
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	return (get_keys(shell, command_line));
}
