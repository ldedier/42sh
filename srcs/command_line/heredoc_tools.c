/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:31:00 by ldedier           #+#    #+#             */
/*   Updated: 2019/07/29 16:35:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** reduces matching \\ into a single one, returns 1 if str ends up with
** a single \ and removes it from the string, else returns 0
*/

int			refine_heredoc(char *str, int apply_expansion)
{
	int		i;

	i = 0;
	if (apply_expansion == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (!str[i + 1])
			{
				str[i] = '\0';
				return (1);
			}
			i++;
		}
		i++;
	}
	return (0);
}

int			heredoc_ret(t_shell *shell, t_command_line *command_line, int ret)
{
	ft_strdel(&command_line->to_append_str);
	command_line->context = E_CONTEXT_STANDARD;
	update_prompt(shell, command_line);
	return (ret);
}

char		*heredoc_ret_str(t_shell *shell,
			t_command_line *command_line, char *str)
{
	ft_strdel(&command_line->to_append_str);
	command_line->context = E_CONTEXT_STANDARD;
	update_prompt(shell, command_line);
	return (str);
}

int			append_to_str(char **str, char *to_append)
{
	if (*str == NULL)
	{
		if (!(*str = ft_strdup(to_append)))
			return (1);
	}
	else if (!(*str = ft_strjoin_free(*str, to_append, 1)))
		return (1);
	return (0);
}
