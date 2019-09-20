/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shortcuts.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 00:41:35 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/19 00:41:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_SHORTCUTS_H
# define SH_SHORTCUTS_H

#include "sh_21.h"

# define VSHORTCUTS		"# vjklhwWeEbB^$0|fFtT;,aAiIrRcCSxXdDyYpPuU"

typedef enum			s_vshortcut_
{
	E_VSHORTCUT_STANDARD,
	E_VSHORTCUT_AWAIT_CHAR,
	E_VSHORTCUT_AWAIT_MOTION
}						t_vshortcut_type;

/*
**
** command:
** 	execute the shortcut
** 		int (1):
**			if the shortcut is a motion_waiting command:
**				the index of the motion result
**			else
**				the awaited character of the command
**		int (2):
**			wether or not the index of the special
**			case is summoned in a motion_waitng command (ie: yy, dd or cc)
**
**	returns SUCCESS or FAILURE
**
** ---------------------------------------------------
**
** motion:
**
**	describes the motion of the shortcut
**	returns the new index of the motion
**
** args:
**	char:	the character of the motion
**		
** ---------------------------------------------------
**
** type:
**
**	wether or not the command awaits a character or a motion
**
*/

typedef struct			s_vshortcut
{
	int					(*command)(t_command_line *, int, int);
	int					(*motion)(t_command_line *m, char);
	t_vshortcut_type	type;
}						t_vshortcut;

/*
********************************************************************************
*/

/*
** sh_vshortcut_u_maj.c
*/
int					sh_vshortcut_u_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_f_maj.c
*/
int					sh_vs_motion_f_maj(
	t_command_line *command_line, char c);

/*
** sh_vshortcut_i.c
*/
int					sh_vshortcut_i(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_t_maj.c
*/
int					sh_vs_motion_t_maj(
	t_command_line *command_line, char c);

/*
** sh_vshortcut_i_maj.c
*/
int					sh_vshortcut_i_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_u.c
*/
int					sh_vshortcut_u(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_e_maj.c
*/
int					sh_vs_motion_e_maj(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_f.c
*/
int					sh_vs_motion_f(t_command_line *command_line, char c);

/*
** sh_vshortcut_r_maj.c
*/
int					sh_vshortcut_r_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_d_maj.c
*/
int					sh_vshortcut_d_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_h.c
*/
int					sh_vs_motion_h(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_d.c
*/
int					sh_vshortcut_d(
	t_command_line *command_line, int index, int special);

/*
** sh_vshortcut_v.c
*/
int					sh_vshortcut_v(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_hashtag.c
*/
int					sh_vshortcut_hashtag(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_w_maj.c
*/
int					sh_vs_motion_w_maj(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_p_maj.c
*/
int					sh_vshortcut_p_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_e.c
*/
int					sh_vs_motion_e(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_comma.c
*/
int					sh_vs_motion_comma(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_b.c
*/
int					sh_vs_motion_b(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_a_maj.c
*/
int					sh_vshortcut_a_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_r.c
*/
int					sh_vshortcut_r(
	t_command_line *command_line, int c, int dummy);

/*
** sh_vshortcut_y_maj.c
*/
int					sh_vshortcut_y_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_s_maj.c
*/
int					sh_vshortcut_s_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_dollar.c
*/
int					sh_vs_motion_dollar(
	t_command_line *command_line, char dummy);

/*
** vshortcuts.c
*/
int					sh_get_single_char(char *c);
int					ft_clamp(int min, int val, int max);
int					execute_motion(
	t_command_line *command_line, int index);
int					execute_vshortcut(
	t_command_line *command_line, t_vshortcut *vshortcut, char c);
int					is_printable_utf8_byte(unsigned char c);
int					execute_motion_awaiting_shortcut(
	t_command_line *command_line,
	t_vshortcut *vshortcut,
	char c,
	char cmd_character);
int					execute_vim_command(
	t_command_line *command_line, char cmd_character);

/*
** sh_vs_motion_w.c
*/
int					sh_vs_motion_w(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_k.c
*/
int					sh_vshortcut_k(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_x.c
*/
int					advance_count_characters(
	t_command_line *command_line,
	int *index,
	int *len,
	int *nb_chars);
int					sh_vshortcut_x(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_x_maj.c
*/
int					sh_vshortcut_x_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_t.c
*/
int					sh_vs_motion_t(t_command_line *command_line, char c);

/*
** sh_vshortcut_a.c
*/
int					sh_vshortcut_a(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_pipe.c
*/
int					sh_vs_motion_pipe(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_semicol.c
*/
int					sh_vs_motion_semicol(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_0.c
*/
int					sh_vs_motion_0(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_C_maj.c
*/
int					sh_vshortcut_C_maj(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_c.c
*/
int					sh_vshortcut_c(
	t_command_line *command_line, int index, int special);

/*
** sh_vs_motion_space.c
*/
int					sh_vs_motion_space(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_p.c
*/
int					sh_vshortcut_p(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vshortcut_j.c
*/
int					sh_vshortcut_j(
	t_command_line *command_line, int dummy, int dummy_2);

/*
** sh_vs_motion_b_maj.c
*/
int					sh_vs_motion_b_maj(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_caret.c
*/
int					sh_vs_motion_caret(
	t_command_line *command_line, char dummy);

/*
** sh_vs_motion_l.c
*/
int					sh_vs_motion_l(
	t_command_line *command_line, char dummy);

/*
** sh_vshortcut_y.c
*/
int					sh_vshortcut_y(
	t_command_line *command_line, int index, int special);

#endif
