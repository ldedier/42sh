/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_from_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:20:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			process_add_choices_from_choice_filler(t_shell *shell,
				t_command_line *cl,
					char *entry, t_choice_filler *c)
{
	char			*fullname;
	t_dlist			**prev_to_add;
	t_dlist			*to_add;
	int				ret;
	t_file			*file;

	if (!(fullname = get_fullname(c, entry)))
		return (1);
	if ((ret = ft_preprocess_choice_add(cl, fullname, &prev_to_add)) != 1)
	{
		if (!(file = new_file(shell, entry, fullname)))
			return (ft_free_turn(fullname, 1));
		if (!sh_pass_filters(file, c->types))
			return (free_file_ret(file, 0));
		if (!(to_add = ft_dlstnew_ptr(file, sizeof(t_file))))
			return (free_file_ret(file, ret));
		add_node_next_to_node(prev_to_add, to_add);
		if (ret)
			cl->autocompletion.choices = cl->autocompletion.choices->prev;
	}
	return (0);
}

int			close_dir_ret(DIR *dir, int ret)
{
	closedir(dir);
	return (ret);
}

int			add_choices_from_dir(t_shell *shell, t_choice_filler *c)
{
	DIR				*dir;
	struct dirent	*entry;
	int				len;

	len = ft_strlen(c->word->to_compare);
	if ((!ft_strcmp(c->transformed_path, "") && !(dir = opendir(".")))
		|| ((ft_strcmp(c->transformed_path, "")
		&& !(dir = opendir(c->transformed_path)))))
		return (0);
	while ((entry = readdir(dir)) != NULL)
	{
		if (!ft_strncmp(entry->d_name, ".", 1) && c->word->to_compare[0] != '.')
			continue;
		if (ft_isprint_only_utf8(entry->d_name)
				&& !ft_strncmp(entry->d_name, c->word->to_compare, len))
		{
			if (process_add_choices_from_choice_filler(shell,
					&g_glob.command_line, entry->d_name, c))
				return (close_dir_ret(dir, 1));
		}
	}
	closedir(dir);
	return (0);
}
