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
	['#'] = {sh_vshortcut_hashtag, NULL, E_VSHORTCUT_STANDARD},
	[' '] = {NULL, sh_vs_motion_space, E_VSHORTCUT_STANDARD},
	['v'] = {sh_vshortcut_v, NULL, E_VSHORTCUT_STANDARD},
	['j'] = {sh_vshortcut_j, NULL, E_VSHORTCUT_STANDARD},
	['k'] = {sh_vshortcut_k, NULL, E_VSHORTCUT_STANDARD},
	['l'] = {NULL, sh_vs_motion_l, E_VSHORTCUT_STANDARD},
	['h'] = {NULL, sh_vs_motion_h, E_VSHORTCUT_STANDARD},
	['w'] = {NULL, sh_vs_motion_w, E_VSHORTCUT_STANDARD},
	['W'] = {NULL, sh_vs_motion_w_maj, E_VSHORTCUT_STANDARD},
	['e'] = {NULL, sh_vs_motion_e, E_VSHORTCUT_STANDARD},
	['E'] = {NULL, sh_vs_motion_e_maj, E_VSHORTCUT_STANDARD},
	['b'] = {NULL, sh_vs_motion_b, E_VSHORTCUT_STANDARD},
	['B'] = {NULL, sh_vs_motion_b_maj, E_VSHORTCUT_STANDARD},
	['^'] = {NULL, sh_vs_motion_caret, E_VSHORTCUT_STANDARD},
	['$'] = {NULL, sh_vs_motion_dollar, E_VSHORTCUT_STANDARD},
	['0'] = {NULL, sh_vs_motion_0, E_VSHORTCUT_STANDARD},
	['|'] = {NULL, sh_vs_motion_pipe, E_VSHORTCUT_STANDARD},
	['f'] = {NULL, sh_vs_motion_f, E_VSHORTCUT_AWAIT_CHAR},
	['F'] = {NULL, sh_vs_motion_f_maj, E_VSHORTCUT_AWAIT_CHAR},
	['t'] = {NULL, sh_vs_motion_t, E_VSHORTCUT_AWAIT_CHAR},
	['T'] = {NULL, sh_vs_motion_t_maj, E_VSHORTCUT_AWAIT_CHAR},
	[';'] = {NULL, sh_vs_motion_semicol, E_VSHORTCUT_STANDARD},
	[','] = {NULL, sh_vs_motion_comma, E_VSHORTCUT_STANDARD},
	['a'] = {sh_vshortcut_a, NULL, E_VSHORTCUT_STANDARD},
	['A'] = {sh_vshortcut_a_maj, NULL, E_VSHORTCUT_STANDARD},
	['i'] = {sh_vshortcut_i, NULL, E_VSHORTCUT_STANDARD},
	['I'] = {sh_vshortcut_i_maj, NULL, E_VSHORTCUT_STANDARD},
	['r'] = {sh_vshortcut_r, NULL, E_VSHORTCUT_AWAIT_CHAR},
	['R'] = {sh_vshortcut_r_maj, NULL, E_VSHORTCUT_STANDARD},
	['c'] = {sh_vshortcut_c, NULL, E_VSHORTCUT_AWAIT_MOTION},
	['C'] = {sh_vshortcut_c_maj, NULL, E_VSHORTCUT_STANDARD},
	['S'] = {sh_vshortcut_s_maj, NULL, E_VSHORTCUT_STANDARD},
	['x'] = {sh_vshortcut_x, NULL, E_VSHORTCUT_STANDARD},
	['X'] = {sh_vshortcut_x_maj, NULL, E_VSHORTCUT_STANDARD},
	['d'] = {sh_vshortcut_d, NULL, E_VSHORTCUT_AWAIT_MOTION},
	['D'] = {sh_vshortcut_d_maj, NULL, E_VSHORTCUT_STANDARD},
	['y'] = {sh_vshortcut_y, NULL, E_VSHORTCUT_AWAIT_MOTION},
	['Y'] = {sh_vshortcut_y_maj, NULL, E_VSHORTCUT_STANDARD},
	['p'] = {sh_vshortcut_p, NULL, E_VSHORTCUT_STANDARD},
	['P'] = {sh_vshortcut_p_maj, NULL, E_VSHORTCUT_STANDARD},
	['u'] = {sh_vshortcut_u, NULL, E_VSHORTCUT_STANDARD},
	['U'] = {sh_vshortcut_u_maj, NULL, E_VSHORTCUT_STANDARD}
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

int			execute_motion(t_command_line *command_line, int index)
{
	int i;
	int char_diff;
	int max;
	int ret;
	int len;

	char_diff = 0;
	
	index = ft_clamp(0, index, command_line->dy_str->current_size - 1);
	i = ft_min(index, command_line->current_index);
	max = ft_max(index, command_line->current_index);
	len = ft_strlen(&command_line->dy_str->str[i]);
	while (i < max
		&& ((size_t)i < command_line->dy_str->current_size - 1 || index != max))
	{
		if ((ret = get_char_len2(0, len,
			(unsigned char *)&command_line->dy_str->str[i])) == -1)
			break ;
		i += ret;
		len -= ret;
		char_diff++;
	}
	char_diff = (index == max ? char_diff : - char_diff);
	command_line->current_index = ft_clamp(0, index,
		command_line->dy_str->current_size - 1);
	render_command_line(command_line, char_diff, 1);
	return (SUCCESS);
}

int				execute_vshortcut(t_command_line *command_line,
		t_vshortcut *vshortcut, char c)
{
	int motion_res;

	if (vshortcut->motion)
	{
		motion_res = vshortcut->motion(command_line, c);
		return (execute_motion(command_line, motion_res));
	}
	else
		return (vshortcut->command(command_line, c, 0));
}

int		is_printable_utf8_byte(unsigned char c)
{
	return (c >= 32 && c <= 126 && !(c & 0b10000000));
}

int			execute_motion_awaiting_shortcut(t_command_line *command_line,
				t_vshortcut *vshortcut, char c, char cmd_character)
{
	t_vshortcut	*motion_shortcut;
	int			motion_res;
	char		suffix_char;

	if (c == cmd_character)
		return (vshortcut->command(command_line, 0, 1));
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
	return (vshortcut->command(command_line, motion_res, 0));
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
