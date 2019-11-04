/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_v.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:44:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_v.c
**
**	copy the content of the command_line in a temp file, open it with vim
**	then execute the content of it
*/

static char		*get_to_edit(t_command_line *command_line)
{
	t_fc_operand	fc;
	t_dlist			*entry_ptr;

	if (command_line->count.active)
	{
		fc.un.integer = command_line->count.value;
		fc.type = E_FC_INTEGER;
		if (!(entry_ptr = get_entry_from_fc_operand(
			&command_line->shell->history,
			&fc, 1)))
			return (sh_perrorn(SH_BLT_HISTORY_RANGE, NULL));
		else
			return (((t_entry *)entry_ptr->content)->command);
	}
	else
		return (command_line->dy_str->str);
}

int				sh_vshortcut_v(t_command_line *command_line,
		int dummy, int dummy_2)
{
	int		fd;
	int		ret;
	char	*to_edit;

	(void)dummy;
	(void)dummy_2;
	if (!(to_edit = get_to_edit(command_line)))
		return (ERROR);
	if ((fd = open(EDIT_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
		return (sh_perror(SH_ERR1_EDIT, "sh_builtin_fc_fill_text"));
	ft_dprintf(fd, "%s\n", to_edit);
	if (sh_execute_editor("vim", command_line->shell) != SUCCESS)
		return (FAILURE);
	render_command_line(command_line, 0, 1);
	get_down_from_command(command_line);
	ret = sh_execute_commands_from_file(command_line->shell, EDIT_FILE);
	flush_command_line(command_line);
	command_line->mode = E_MODE_INSERT;
	if (update_prompt(command_line->shell, command_line))
		return (FAILURE);
	render_command_line(command_line, -g_glob.cursor, 1);
	return (ret);
}
