/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:47:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/08 19:37:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		fill_indexes(t_command_line *command_line, int *index_a,
	int *index_b)
{
	if (command_line->current_index == (int)command_line->dy_str->current_size)
	{
		*index_b = get_left_w_char_index(command_line);
		*index_a = get_left_w_char_index_dy_str(command_line->dy_str, *index_b);
	}
	else if (command_line->current_index == 0)
	{
		*index_a = 0;
		*index_b = get_right_w_char_index(command_line);
	}
	else
	{
		*index_a = get_left_w_char_index(command_line);
		*index_b = command_line->current_index;
	}
}

static void		transpose_str(char *str, int index_a, int index_b)
{
	int		len_a;
	int		len_b;
	char	buff[5];

	len_a = get_char_len_unprotected(index_a, (unsigned char *)str);
	len_b = get_char_len_unprotected(index_b, (unsigned char *)str);
	ft_bzero(buff, sizeof(buff));
	ft_strncpy(buff, &str[index_a], len_a);
	ft_strncpy(&str[index_a], &str[index_b], len_b);
	ft_strncpy(&str[index_a + len_b], buff, len_a);
}

static void		prepare_transpose_motion(t_command_line *command_line,
		int *motion, int index_a, int index_b)
{
	if (command_line->current_index == 0)
	{
		*motion = get_char_len(index_b,
			(unsigned char *)command_line->dy_str->str);
	}
	else
	{
		command_line->current_index += get_char_len(index_b,
			(unsigned char *)command_line->dy_str->str) - get_char_len(index_a,
				(unsigned char *)command_line->dy_str->str);
		*motion = get_char_len(index_a,
			(unsigned char *)command_line->dy_str->str);
	}
}

int				process_ctrl_t(t_command_line *command_line)
{
	int index_a;
	int index_b;
	int motion;
	int ret;

	if (ft_strlen_utf8(command_line->dy_str->str) < 2)
		return (SUCCESS);
	if ((ret = sh_save_command_line(command_line)) != SUCCESS)
		return (ret);
	fill_indexes(command_line, &index_a, &index_b);
	prepare_transpose_motion(command_line, &motion, index_a, index_b);
	transpose_str(command_line->dy_str->str, index_a, index_b);
	execute_motion(command_line,
		command_line->current_index + motion, 0);
	return (SUCCESS);
}
