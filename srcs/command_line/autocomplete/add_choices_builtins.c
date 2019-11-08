/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:24:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 19:06:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		process_add_choices_from_name(t_shell *shell,
			t_command_line *command_line, char *name)
{
	char			*fullname;
	t_dlist			**prev_to_add;
	t_dlist			*to_add;
	int				ret;
	t_file			*file;

	if (!(fullname = ft_strdup(name)))
		return (1);
	if ((ret = ft_preprocess_choice_add(command_line,
			fullname, &prev_to_add)) != 1)
	{
		if (!(file = new_file(shell, fullname, fullname)))
			return (ft_free_turn(fullname, 1));
		if (!(to_add = ft_dlstnew_ptr(file, sizeof(t_file))))
		{
			free_file(file);
			return (sh_perror(SH_ERR1_MALLOC, "process_add_choices_from_name"));
		}
		add_node_next_to_node(prev_to_add, to_add);
		if (ret)
			command_line->autocompletion.choices =
				command_line->autocompletion.choices->prev;
	}
	return (SUCCESS);
}

int		add_choices_builtins(t_shell *shell, t_word *word)
{
	t_builtin_container	*builtin_containers;
	int					i;
	int					len;

	len = ft_strlen(word->to_compare);
	i = 0;
	builtin_containers = get_builtins();
	while (i < NB_BUILTINS)
	{
		if (!ft_strncmp(builtin_containers[i].name, word->to_compare, len))
		{
			if (process_add_choices_from_name(shell, &g_glob.command_line,
					builtin_containers[i].name))
				return (FAILURE);
		}
		i++;
	}
	return (0);
}
