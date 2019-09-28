/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshortcuts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/20 07:28:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static t_vshortcut	g_vshortcuts_arr[0xff] =
{
	['#'] = {sh_vshortcut_hashtag, NULL, E_VSHORTCUT_STANDARD, -1},
	['v'] = {sh_vshortcut_v, NULL, E_VSHORTCUT_STANDARD, -1},
	['j'] = {sh_vshortcut_j, NULL, E_VSHORTCUT_STANDARD, -1},
	['k'] = {sh_vshortcut_k, NULL, E_VSHORTCUT_STANDARD, -1},
	[' '] = {NULL, sh_vs_motion_space, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['l'] = {NULL, sh_vs_motion_l, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['h'] = {NULL, sh_vs_motion_h, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['w'] = {NULL, sh_vs_motion_w, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['W'] = {NULL, sh_vs_motion_w_maj, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['e'] = {NULL, sh_vs_motion_e, E_VSHORTCUT_STANDARD, E_MOTION_IN},
	['E'] = {NULL, sh_vs_motion_e_maj, E_VSHORTCUT_STANDARD, E_MOTION_IN},
	['b'] = {NULL, sh_vs_motion_b, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['B'] = {NULL, sh_vs_motion_b_maj, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['^'] = {NULL, sh_vs_motion_caret, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['$'] = {NULL, sh_vs_motion_dollar, E_VSHORTCUT_STANDARD, E_MOTION_IN},
	['0'] = {NULL, sh_vs_motion_0, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['|'] = {NULL, sh_vs_motion_pipe, E_VSHORTCUT_STANDARD, E_MOTION_EX},
	['f'] = {NULL, sh_vs_motion_f, E_VSHORTCUT_AWAIT_CHAR, E_MOTION_IN},
	['F'] = {NULL, sh_vs_motion_f_maj, E_VSHORTCUT_AWAIT_CHAR, E_MOTION_EX},
	['t'] = {NULL, sh_vs_motion_t, E_VSHORTCUT_AWAIT_CHAR, E_MOTION_IN},
	['T'] = {NULL, sh_vs_motion_t_maj, E_VSHORTCUT_AWAIT_CHAR, E_MOTION_EX},
	[';'] = {NULL, sh_vs_motion_semicol, E_VSHORTCUT_STANDARD, E_MOTION_COPY},
	[','] = {NULL, sh_vs_motion_comma, E_VSHORTCUT_STANDARD, E_MOTION_INV},
	['a'] = {sh_vshortcut_a, NULL, E_VSHORTCUT_STANDARD, -1},
	['A'] = {sh_vshortcut_a_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['i'] = {sh_vshortcut_i, NULL, E_VSHORTCUT_STANDARD, -1},
	['I'] = {sh_vshortcut_i_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['r'] = {sh_vshortcut_r, NULL, E_VSHORTCUT_AWAIT_CHAR, -1},
	['R'] = {sh_vshortcut_r_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['c'] = {sh_vshortcut_c, NULL, E_VSHORTCUT_AWAIT_MOTION, -1},
	['C'] = {sh_vshortcut_c_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['S'] = {sh_vshortcut_s_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['x'] = {sh_vshortcut_x, NULL, E_VSHORTCUT_STANDARD, -1},
	['X'] = {sh_vshortcut_x_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['d'] = {sh_vshortcut_d, NULL, E_VSHORTCUT_AWAIT_MOTION, -1},
	['D'] = {sh_vshortcut_d_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['y'] = {sh_vshortcut_y, NULL, E_VSHORTCUT_AWAIT_MOTION, -1},
	['Y'] = {sh_vshortcut_y_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['p'] = {sh_vshortcut_p, NULL, E_VSHORTCUT_STANDARD, -1},
	['P'] = {sh_vshortcut_p_maj, NULL, E_VSHORTCUT_STANDARD, -1},
	['u'] = {sh_vshortcut_u, NULL, E_VSHORTCUT_STANDARD, E_MOTION_NO_SAVE},
	['U'] = {sh_vshortcut_u_maj, NULL, E_VSHORTCUT_STANDARD, E_MOTION_NO_SAVE}
};

int		sh_get_single_char(char *c)
{
	int		ret;
	char	buffer[4];

	ret = read(0, buffer, 4);
	if (ret == -1)
		return (sh_perror(SH_ERR1_READ, "sh_get_single_char"));
	if (ret == 1)
		*c = buffer[0];
	else
		*c = -1;
	return (SUCCESS);
}

int			ft_clamp(int min, int val, int max)
{
	if (val < min)
		return (min);
	else if (val > max)
		return (max);
	return (val);
}

int			execute_motion(t_command_line *line, int index, int vi)
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
	len = ft_strlen(&line->dy_str->str[i]);
	while (i < max
		&& ((size_t)i < line->dy_str->current_size - vi || index != max))
	{
		if ((ret = get_char_len2(0, len,
			(unsigned char *)&line->dy_str->str[i])) == -1)
		{
			break ;
		}
		i += ret;
		len -= ret;
		char_diff++;
	}
	char_diff = (index == max ? char_diff : - char_diff);
	line->current_index = ft_clamp(0, index, line->dy_str->current_size - vi);
	render_command_line(line, char_diff, 1);
	return (SUCCESS);
}

int				execute_vsh_command(t_command_line *command_line,
					t_vshortcut *vshortcut, char c, int cmd_suffix)
{

	if (vshortcut->inclusion != E_MOTION_NO_SAVE &&
		sh_save_command_line(command_line) != SUCCESS)
	{
		return (FAILURE);
	}
	return (vshortcut->command(command_line, c, cmd_suffix));
}

int				execute_vshortcut(t_command_line *command_line,
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

int		is_printable_utf8_byte(unsigned char c)
{
	return (c >= 32 && c <= 126 && !(c & 0b10000000));
}

int		get_inclusion(t_command_line *command_line,
			t_motion_inclusion inclusion)
{
	if ((inclusion == E_MOTION_COPY || inclusion == E_MOTION_INV)
		&& command_line->last_ft_command.motion)
	{
		if (command_line->last_ft_command.motion == &sh_vs_motion_t
				|| command_line->last_ft_command.motion == &sh_vs_motion_f)
		{
			return (inclusion == E_MOTION_COPY ? E_MOTION_IN : E_MOTION_EX);
		}
		else
			return (inclusion == E_MOTION_COPY ? E_MOTION_EX : E_MOTION_IN);
	}
	else
		return (inclusion);
}

int			execute_motion_awaiting_shortcut(t_command_line *command_line,
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
	{
		return (SUCCESS);
	}
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

int			execute_vim_command(t_command_line *command_line,
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
			if (sh_get_single_char(&suffix_char))
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
