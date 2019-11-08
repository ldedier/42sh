/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:09:10 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:15:27 by ldedier          ###   ########.fr       */
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

int			free_file_ret(t_file *file, int ret)
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

char		*get_fullname(t_choice_filler *c, char *entry)
{
	char *fullname;

	if (!c->path && !c->suffix && !(fullname = ft_strdup(entry)))
		return (NULL);
	else if (c->path && !c->suffix &&
		!(fullname = ft_strjoin(c->path, entry)))
		return (NULL);
	else if (!c->path && c->suffix &&
		!(fullname = ft_strjoin(entry, c->suffix)))
		return (NULL);
	else if (c->path && c->suffix &&
		!(fullname = ft_strjoin_3(c->path, entry, c->suffix)))
		return (NULL);
	return (fullname);
}
