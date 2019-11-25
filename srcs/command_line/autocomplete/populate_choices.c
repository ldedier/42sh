/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_choices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:03:42 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 03:23:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			add_choices_path(t_shell *shell, t_word *word, char *path_str)
{
	char			*path;
	t_choice_filler	c;

	c.word = word;
	c.types = -1;
	c.path = NULL;
	c.suffix = NULL;
	while ((path = ft_strsep(&path_str, ":")))
	{
		c.transformed_path = path;
		if (add_choices_from_dir(shell, &c))
		{
			ft_strsep(NULL, NULL);
			return (1);
		}
	}
	return (0);
}

int			populate_choices_from_binaries(t_shell *shell, t_word *word)
{
	char *path_str;

	free(word->to_compare);
	if (!(word->to_compare = ft_strdup(word->str)))
		return (1);
	if ((path_str = sh_vars_get_value(shell->env, NULL, "PATH")))
	{
		if (add_choices_path(shell, word, path_str))
			return (1);
		if (add_choices_builtins(shell, word))
			return (1);
		return (0);
	}
	else if (add_choices_builtins(shell, word))
		return (1);
	return (0);
}

int			populate_choices_from_folder(t_shell *shell,
	t_word *word, int types)
{
	char			*file;
	t_choice_filler	c;

	c.word = word;
	c.types = types;
	c.suffix = NULL;
	if (get_path_and_file_from_str(c.word->str,
			&c.transformed_path, &file))
		return (1);
	if (!(c.path = ft_strdup(c.transformed_path)))
	{
		free(file);
		return (ft_free_turn(c.transformed_path, 1));
	}
	free(word->to_compare);
	if (!(word->to_compare = ft_strdup(file)))
		return (ft_free_turn_3(file, c.transformed_path, c.path, FAILURE));
	if (!ft_strncmp(c.path, "~/", 2)
			&& process_subst_home(shell, &c.transformed_path))
		return (ft_free_turn_3(file, c.transformed_path, c.path, 1));
	if (add_choices_from_dir(shell, &c))
		return (ft_free_turn_3(file, c.transformed_path, c.path, FAILURE));
	return (ft_free_turn_3(file, c.transformed_path, c.path, SUCCESS));
}

static int	populate_choices_from_binaries_then_folder(t_shell *shell,
	t_command_line *command_line, t_word *word)
{
	if (populate_choices_from_binaries(shell, word))
		return (1);
	if (command_line->autocompletion.choices == NULL)
	{
		if (populate_choices_from_folder(shell, word, -1))
			return (1);
	}
	if (populate_choices_from_expansions(command_line, shell, word))
		return (1);
	return (0);
}

int			populate_choices_from_word(t_command_line *cl,
		t_shell *shell, t_word *word)
{
	t_symbol *symbol;

	if (!(word->token))
	{
		if (populate_choices_from_binaries_then_folder(shell, cl, word))
			return (1);
		return (0);
	}
	symbol = word->token->ast_node->parent->symbol;
	if (symbol->id == sh_index(CMD_NAME))
	{
		if (populate_choices_from_binaries_then_folder(shell, cl, word))
			return (1);
	}
	else if (symbol->id == sh_index(FILENAME) &&
		populate_choices_from_folder(shell, word, -1))
		return (1);
	else if (populate_choices_from_folder(shell, word, -1))
		return (1);
	if (populate_choices_from_expansions(cl, shell, word))
		return (1);
	return (0);
}
