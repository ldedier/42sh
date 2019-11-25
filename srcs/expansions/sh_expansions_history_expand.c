/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_history_expand.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/25 11:00:48 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			ft_word_delim_len(char *str, int delim)
{
	int		i;

	i = 0;
	while (str[i] && !ft_iswhite(str[i]) && str[i] != delim)
		i++;
	return (i);
}

char		*ft_strdup_word_delim(char *str, int delim)
{
	char	*res;
	int		len;

	len = ft_word_delim_len(str, delim);
	if (!(res = ft_strnew(len)))
		return (sh_perrorn(SH_ERR1_MALLOC, "ft_strdup_word_delim"));
	ft_strncpy(res, str, len);
	res[len] = '\0';
	return (res);
}

static void	parse_fc_operand_expansion(t_fc_operand *operand,
		char *str)
{
	int		error;

	operand->un.integer = sh_atoi_fc(str, &error);
	if (error || operand->un.integer == 0)
	{
		if (!ft_strcmp("!", str))
		{
			operand->type = E_FC_INTEGER;
			operand->un.integer = -1;
		}
		else
		{
			operand->type = E_FC_STRING;
			operand->un.string = str;
		}
	}
	else
		operand->type = E_FC_INTEGER;
	operand->parsed = 1;
}

int			sh_process_history_expand(t_shell *shell,
		t_command_line *command_line, int *index, char *double_quoted)
{
	char			*str;
	t_fc_operand	operand;
	t_dlist			*entry_ptr;
	t_entry			*entry;
	int				len;

	if (!(str = ft_strdup_word_delim(&command_line->dy_str->str[*index + 1],
		*double_quoted == 1 ? '"' : '\0')))
		return (FAILURE);
	len = ft_strlen(str);
	parse_fc_operand_expansion(&operand, str);
	if (!(entry_ptr = get_entry_from_fc_operand(&shell->history, &operand, 0)))
	{
		ft_dprintf(2, "%s!%s: %s%s\n", SH_ERR_COLOR,
			str, SH_ERR1_EVENT_NOT_FOUND, EOC);
		free(str);
		return (ERROR);
	}
	free(str);
	entry = entry_ptr->content;
	if (ft_substitute_dy_str(command_line->dy_str,
		entry->command, *index, len + 1))
		return (sh_perror(SH_ERR1_MALLOC, "sh_history_expand"));
	index += len + 1;
	return (SUCCESS);
}
