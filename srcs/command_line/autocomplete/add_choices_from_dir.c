/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_from_dir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/14 14:52:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		add_node_next_to_node(t_dlist **node, t_dlist *to_add)
{
	t_dlist *tmp;

	if (*node)
	{
		tmp = (*node)->next;
		(*node)->next = to_add;
		(to_add)->prev = (*node);
		(to_add)->next = tmp;
		(to_add)->next->prev = to_add;
	}
	else
		*node = to_add;
}

static int	free_file_ret(t_file *file, int ret)
{
	free_file(file);
	return (ret);
}

int			sh_pass_filters(t_file *file, int types)
{
	mode_t mode;

	if (file->unstatable)
		return (1);
	else
	{
		mode = file->st.st_mode & S_IFMT;
		return (types & mode);
	}
}

int			process_add_choices_from_dir(t_shell *shell,
				t_command_line *command_line,
					struct dirent *entry, t_dir_chooser *c)
{
	char			*fullname;
	t_dlist			**prev_to_add;
	t_dlist			*to_add;
	int				ret;
	t_file			*file;

	if (!c->path && !(fullname = ft_strdup_escaped(entry->d_name)))
		return (1);
	else if (c->path &&
		!(fullname = ft_strjoin_escaped(c->path, entry->d_name)))
		return (1);
	if ((ret = ft_preprocess_choice_add(command_line,
					fullname, &prev_to_add)) != 1)
	{
		if (!(file = new_file(shell, entry->d_name, fullname)))
			return (ft_free_turn(fullname, 1));
		if (!sh_pass_filters(file, c->types))
			return (free_file_ret(file, 0));
		if (!(to_add = ft_dlstnew_ptr(file, sizeof(t_file))))
			return (free_file_ret(file, ret));
		add_node_next_to_node(prev_to_add, to_add);
		if (ret)
			command_line->autocompletion.choices =
				command_line->autocompletion.choices->prev;
	}
	return (0);
}

//word
//char *c->transformed_path,
//		char *prefix)
int			add_choices_from_dir(t_shell *shell, t_dir_chooser *c)
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
			if (process_add_choices_from_dir(shell,
						&g_glob.command_line, entry, c))
			{
				closedir(dir);
				return (1);
			}
		}
	}
	closedir(dir);
	return (0);
}
