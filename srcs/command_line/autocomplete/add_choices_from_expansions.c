/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_choices_from_expansions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 23:21:55 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/07 23:21:55 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** returns 0 if the entry does not match with the comparison
** returns 1 if the entry key match with the comparison
** returns 2 if the entry key is equal to the comparison
**
** updates the index of the equal character of the entry throughout the process
*/

int		sh_match_key(char *entry, char *to_compare, int *equal_index)
{
	int i;

	i = 0;
	*equal_index = 0;
	while (to_compare[i] && entry[i] != '=')
	{
		if (entry[i] != to_compare[i])
			return (0);
		i++;
	}
	if (entry[i] == '=' && !to_compare[i])
	{
		*equal_index = i;
		return (2);
	}
	else if (!to_compare[i])
	{
		while (entry[i] != '=')
			i++;
		*equal_index = i;
		return (1);
	}
	return (0);
}


int populate_keys_from_dy_tab(t_dy_tab *dtab,
	t_shell *shell, t_choice_filler *c)
{
	int		i;
	int		ret;
	int		equal_index;
	char	*key;

	i = 0;
	while (i < (int)dtab->current_size)
	{
		if ((ret = sh_match_key(dtab->tbl[i], c->word->to_compare, &equal_index)))
		{
			if (!(key = ft_strndup(dtab->tbl[i], equal_index)))
				return (FAILURE);
			if (process_add_choices_from_choice_filler(shell, &g_glob.command_line,
				key, c))
			{
				free(key);
				return (FAILURE);
			}
			free(key);
		}
		i++;
	}
	return (0);
}

int		get_end_index(char *str, int index)
{
	while (str[index] && str[index] != '$')
		index++;
	return (index);
}

int		process_fill_choice_filler_expansion(t_choice_filler *c,
			int *last_dollar_index, int exp_braced)
{
	int		end_index;

	if (!(c->path = ft_strndup(c->word->str, *last_dollar_index + 1)))
		return (FAILURE);
	end_index = get_end_index(c->word->str, *last_dollar_index + 1);
	if (!(c->word->to_compare
				= ft_strndup(&c->word->str[*last_dollar_index + 1],
					end_index - (*last_dollar_index + 1))))
		return (sh_perror(SH_ERR1_MALLOC,
			"process_fill_choice_filler_expansion (1)"));
	if (!(c->suffix = ft_strdup(&c->word->str[end_index])))
		return (sh_perror(SH_ERR1_MALLOC,
			"process_fill_choice_filler_expansion (2)"));
	if (exp_braced)
	{
		if (!(c->suffix = ft_strjoin_free("}", c->suffix, 2)))
			return (sh_perror(SH_ERR1_MALLOC,
				"process_fill_choice_filler_expansion (3)"));
	}
	return (SUCCESS);
}

int		fill_choice_filler_expansion(t_choice_filler *c,
			int *last_dollar_index)
{
	int		i;
	int		exp_braced;

	exp_braced = 0;
	*last_dollar_index = -1;
	i = 0;
	while (c->word->str[i] && i < c->word->index_char_offset)
	{
		if (c->word->str[i] == '$')
			*last_dollar_index = i;
		i++;
	}
	if (*last_dollar_index == -1)
		return (FAILURE);
	if (i > *last_dollar_index && c->word->str[*last_dollar_index + 1] == '{')
	{
		exp_braced = 1;
		(*last_dollar_index)++;
	}
	return (process_fill_choice_filler_expansion(c, last_dollar_index,
		exp_braced));
}

int		free_turn_choice_filler(t_choice_filler *c, int ret)
{
	ft_strdel(&c->suffix);
	ft_strdel(&c->path);
	ft_strdel(&c->word->to_compare);
	return (ret);
}

int		populate_choices_from_expansions(t_command_line *command_line,
		t_shell *shell, t_word *word)
{
	t_choice_filler c;
	int				dollar_index;

	(void)command_line;
	c.word = word;
	c.types = -1;
	c.suffix = NULL;
	c.path = NULL;
	c.word->to_compare = NULL;
	if (fill_choice_filler_expansion(&c, &dollar_index))
	{
		if (dollar_index == -1)
			return (SUCCESS);
		return (free_turn_choice_filler(&c, FAILURE));
	}
	if (populate_keys_from_dy_tab(shell->env, shell, &c))
		return (free_turn_choice_filler(&c, FAILURE));
	if (populate_keys_from_dy_tab(shell->vars, shell, &c))
		return (free_turn_choice_filler(&c, FAILURE));
	return (free_turn_choice_filler(&c, SUCCESS));
}
