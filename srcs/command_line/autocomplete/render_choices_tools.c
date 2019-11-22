/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_choices_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 02:26:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/06/07 00:22:11 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_get_file_len(t_file *file)
{
	return (ft_strlen_utf8(file->name) + (!file->unstatable
			&& S_ISDIR(file->st.st_mode)));
}

int		sh_get_max_file_len(t_dlist *dlist)
{
	t_dlist	*ptr;
	t_file	*file;
	int		first;
	int		ret;
	int		max;

	max = 0;
	ptr = dlist;
	first = 1;
	while ((ptr != dlist && ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		if ((ret = sh_get_file_len(file)) > max)
			max = ret;
		ptr = ptr->next;
		first = 0;
	}
	return (max);
}

int		ft_round(float a)
{
	if (a == (int)a)
		return ((int)a);
	else
		return ((int)a + 1);
}

int		lines_rendered_from_file(t_file *file)
{
	int ret;

	ret = ft_max(1, (sh_get_file_len(file) / (g_glob.winsize.ws_col + 1)) + 1);
	return (ret);
}

int		command_line_visible_lines(t_command_line *command_line)
{
	t_dlist *ptr;
	int		res;
	int		first;
	t_file	*file;

	if (command_line->autocompletion.nb_cols > 1)
		return (command_line->autocompletion.nb_lines);
	first = 1;
	res = 0;
	ptr = command_line->autocompletion.choices;
	while ((ptr != command_line->autocompletion.choices
		&& ptr != NULL) || (first && ptr != NULL))
	{
		file = (t_file *)ptr->content;
		first = 0;
		res += lines_rendered_from_file(file);
		ptr = ptr->next;
	}
	return (res);
}
