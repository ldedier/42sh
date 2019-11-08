/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vshortcuts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:23:57 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/08 17:36:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

t_vshortcut	g_vshortcuts_arr[0xff] =
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
