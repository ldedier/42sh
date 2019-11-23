/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:01:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/23 03:03:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		init_expander(t_history_expander *he)
{
	he->single_quoted = 0;
	he->double_quoted = 0;
	he->backslashed = 0;
	he->bracket = 0;
}

int			is_eligible_for_history_expansion(t_command_line *command_line,
	int *i, t_history_expander *he)
{
	return (command_line->dy_str->str[*i] == '!'
		&& !he->backslashed && !he->single_quoted
			&& (*i != (int)command_line->dy_str->current_size - 1
				&& !ft_iswhite(command_line->dy_str->str[*i + 1])
					&& command_line->dy_str->str[*i + 1] != '=')
						&& !he->bracket);
}

int			sh_history_expand(t_command_line *command_line,
	int *i, t_history_expander *he, t_shell *shell)
{
	int ret;

	if (*i > 0 && command_line->dy_str->str[*i - 1] == '[')
		return (SUCCESS);
	*he->expanded = 1;
	if ((ret = sh_process_history_expand(shell, command_line, i,
					&he->double_quoted)) != SUCCESS)
	{
		return (ret);
	}
	return (SUCCESS);
}

int			scan_expansions_history(int *i, t_shell *shell,
	t_command_line *command_line, t_history_expander *he)
{
	int ret;

	if (command_line->dy_str->str[*i] == '\\')
		he->backslashed = !he->backslashed;
	else if (command_line->dy_str->str[*i] == '\'' && !he->backslashed)
		he->single_quoted = !he->single_quoted;
	else if (command_line->dy_str->str[*i] == '\"' && !he->backslashed)
		he->double_quoted = !he->double_quoted;
	else if (command_line->dy_str->str[*i] == '[' && !he->backslashed)
		he->bracket = 1;
	else if (command_line->dy_str->str[*i] == ']' && !he->backslashed)
		he->bracket = 0;
	else if (is_eligible_for_history_expansion(command_line, i, he))
	{
		if ((ret = sh_history_expand(command_line, i, he, shell)))
			return (ret);
	}
	else
		he->backslashed = 0;
	return (SUCCESS);
}

int			sh_expansions_history(t_shell *shell, t_command_line *command_line,
		int *expanded)
{
	int					i;
	t_history_expander	he;
	int					ret;

	init_expander(&he);
	he.expanded = expanded;
	i = 0;
	*he.expanded = 0;
	while (i < (int)command_line->dy_str->current_size)
	{
		if ((ret = scan_expansions_history(&i, shell, command_line, &he)))
			return (ret);
		i++;
	}
	return (SUCCESS);
}
