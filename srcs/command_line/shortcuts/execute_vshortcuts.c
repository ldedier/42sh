/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_vshortcuts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:55:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/20 20:51:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		execute_motion(t_command_line *line, int index, int vi)
{
	int i;
	int char_diff;
	int max;
	int ret;
	int len;

	char_diff = 0;
	index = ft_clamp(0, index, line->dy_str->current_size - vi);
	i = ft_max(ft_min(index, line->current_index), 0);
	max = ft_max(index, line->current_index);
	len = ft_strlen(&line->dy_str->str[i]) - vi;
	while (i < max
		&& ((size_t)i < line->dy_str->current_size - vi || index != max))
	{
		if ((ret = get_char_len2(0, len,
			(unsigned char *)&line->dy_str->str[i])) == -1)
			break ;
		i += ret;
		len -= ret;
		char_diff++;
	}
	char_diff = (index == max ? char_diff : -char_diff);
	line->current_index = ft_clamp(0, index, i);
	render_command_line(line, char_diff, 1);
	return (SUCCESS);
}

int		execute_vsh_command(t_command_line *command_line,
					t_vshortcut *vshortcut, int c, int cmd_suffix)
{
	if (vshortcut->inclusion != E_MOTION_NO_SAVE &&
		sh_save_command_line(command_line) != SUCCESS)
	{
		return (FAILURE);
	}
	return (vshortcut->command(command_line, c, cmd_suffix));
}

int		execute_vshortcut(t_command_line *command_line,
		t_vshortcut *vshortcut, char c)
{
	int motion_res;

	if (vshortcut->motion)
	{
		motion_res = vshortcut->motion(command_line, c);
		return (execute_motion(command_line, motion_res, 1));
	}
	else
		return (execute_vsh_command(command_line, vshortcut, c, 0));
}

int		execute_motion_awaiting_shortcut(t_command_line *command_line,
				t_vshortcut *vshortcut, char c, char cmd_character)
{
	t_vshortcut			*motion_shortcut;
	int					motion_res;
	char				suffix_char;

	if (c == cmd_character)
	{
		return (execute_vsh_command(command_line, vshortcut,
			0, E_MOTION_SPECIAL));
	}
	if (!ft_strchr(VSHORTCUTS, c)
		|| !(motion_shortcut = &g_vshortcuts_arr[(int)c])
		|| !motion_shortcut->motion)
		return (SUCCESS);
	if (motion_shortcut->type == E_VSHORTCUT_STANDARD)
		motion_res = motion_shortcut->motion(command_line, 0);
	else
	{
		if (sh_get_single_char(&suffix_char))
			return (FAILURE);
		if (!is_printable_utf8_byte(suffix_char))
			return (SUCCESS);
		motion_res = motion_shortcut->motion(command_line, suffix_char);
	}
	return (execute_vsh_command(command_line, vshortcut, motion_res,
		get_inclusion(command_line, motion_shortcut->inclusion)));
}

int		execute_vim_command(t_command_line *command_line,
				char cmd_character)
{
	t_vshortcut	*vsc;
	char		suffix_char;

	if (!ft_strchr(VSHORTCUTS, cmd_character)
		|| !(vsc = &g_vshortcuts_arr[(int)cmd_character]))
		return (SUCCESS);
	else
	{
		flush_keys(&command_line->buffer);
		if (vsc->type == E_VSHORTCUT_STANDARD)
			return (execute_vshortcut(command_line, vsc, 0));
		else
		{
			if (get_motion_suffix_char(command_line, &suffix_char))
				return (FAILURE);
			if (!is_printable_utf8_byte(suffix_char))
				return (SUCCESS);
			if (vsc->type == E_VSHORTCUT_AWAIT_CHAR)
				return (execute_vshortcut(command_line, vsc, suffix_char));
			else
				return (execute_motion_awaiting_shortcut(command_line,
					vsc, suffix_char, cmd_character));
		}
	}
}
