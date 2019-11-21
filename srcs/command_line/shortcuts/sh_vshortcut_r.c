/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_vshortcut_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:02:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/04 18:39:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_vshortcut_r.c
**
** replace the counth next characters by c
*/

static char	*alloc_replacement(int count, char c)
{
	char	*res;
	int		i;

	if (!(res = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = c;
		i++;
	}
	res[i] = '\0';
	return (res);
}

int			sh_vshortcut_r(t_command_line *command_line, int c, int dummy)
{
	int		i;
	int		nb_chars;
	char	*replacement;
	int		len;

	(void)dummy;
	if (advance_count_characters(command_line, &i, &len, &nb_chars) != SUCCESS)
		return (FAILURE);
	if (!(replacement = alloc_replacement(nb_chars, c)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_vshortcut_r"));
	if (ft_substitute_dy_str(command_line->dy_str, replacement,
		command_line->current_index, len))
	{
		free(replacement);
		return (FAILURE);
	}
	free(replacement);
	render_command_line(command_line, 0, 1);
	return (SUCCESS);
}
