/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:39:36 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 20:22:21 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_command_line(t_command_line *command_line)
{
	ft_dlstdel(&command_line->autocompletion.choices, free_file_dlst);
	ft_dy_str_free(&command_line->dy_str);
	ft_dy_str_free(&command_line->searcher.dy_str);
	ft_strdel(&command_line->prompt);
	ft_strdel(&command_line->clipboard);
	ft_strdel(&command_line->edit_line);
	ft_lstdel(&command_line->saves_stack, t_save_free_list);
}
