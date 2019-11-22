/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:37:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/06 11:27:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		ft_strlen_utf8(char *str)
{
	int i;
	int res;

	if (!str)
		return (-1);
	i = 0;
	res = 0;
	while (str[i])
	{
		if (!(str[i] & 0b10000000))
			i++;
		else if (str[i] & 0b01000000 && !(str[i] & 0b00100000))
			i += 2;
		else if (str[i] & 0b00100000 && !(str[i] & 0b00010000))
			i += 3;
		else if (str[i] & 0b000100000 && !(str[i] & 0b00001000))
			i += 4;
		else
			i++;
		res++;
	}
	return (res);
}

int		ft_strnlen_utf8(char *str, int n)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i] && i < n)
	{
		if (!(str[i] & 0b10000000))
			i++;
		else if (str[i] & 0b01000000 && !(str[i] & 0b00100000))
			i += 2;
		else if (str[i] & 0b00100000 && !(str[i] & 0b00010000))
			i += 3;
		else if (str[i] & 0b000100000 && !(str[i] & 0b00001000))
			i += 4;
		else
			i++;
		res++;
	}
	return (res);
}

int		get_left_w_char_index_dy_str(t_dy_str *dy_str, int index)
{
	int				j;
	unsigned char	*buffer;

	if (index == 0)
		return (0);
	else
	{
		j = 1;
		while (index - j >= 0 && j < 5)
		{
			buffer = (unsigned char *)&(dy_str->str[index - j]);
			if (is_printable_utf8(buffer, j))
				return (index - j);
			j++;
		}
	}
	return (index - j);
}

int		get_left_w_char_index(t_command_line *command_line)
{
	unsigned char	*buffer;
	int				j;

	j = 1;
	while ((int)command_line->current_index - j >= 0 && j < 5)
	{
		buffer = (unsigned char *)
			&(command_line->dy_str->str[command_line->current_index - j]);
		if (is_printable_utf8(buffer, j))
			return (command_line->current_index - j);
		j++;
	}
	return (command_line->current_index);
}

int		get_right_w_char_index(t_command_line *command_line)
{
	unsigned char	*buffer;
	int				i;

	buffer = (unsigned char *)
		&(command_line->dy_str->str[command_line->current_index]);
	i = 1;
	while (i < ft_min(5, (int)(command_line->dy_str->current_size -
					command_line->current_index + 1)))
	{
		if (is_printable_utf8(buffer, i))
			return (i + command_line->current_index);
		i++;
	}
	return (command_line->current_index);
}
