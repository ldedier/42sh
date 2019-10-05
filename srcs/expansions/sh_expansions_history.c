/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expansions_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 12:01:07 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/29 12:01:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int ft_word_delim_len(char *str, int delim)
{
	int i;

	i = 0;
	while (str[i] && !ft_iswhite(str[i]) && str[i] != delim)
		i++;
	return (i);
}

char	*ft_strdup_word_delim(char *str, int delim)
{
	char	*res;
	int		i;
	int		len;

	len = ft_word_delim_len(str, delim);
	if (!(res = ft_strnew(len)))
		return (sh_perrorn(SH_ERR1_MALLOC, "ft_strdup_word_delim"));
	i = 0;
	ft_strncpy(res, str, len);
	res[len] = '\0';
	return (res);

}

static void	parse_fc_operand_expansion(t_fc_operand *operand,
		char *str)
{
	int error;

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

int		sh_history_expand(t_shell *shell,
		t_command_line *command_line, int *index, int *double_quoted)
{
	char			*str;
	t_fc_operand	operand;
	t_dlist			*entry_ptr;
	t_entry			*entry;
	int				len;

	(void)shell;
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

int		sh_expansions_history(t_shell *shell, t_command_line *command_line,
		int *expanded)
{
	int i;
	int single_quoted;
	int double_quoted;
	int backslashed;
	int ret;

	single_quoted = 0;
	backslashed = 0;
	i = 0;
	*expanded = 0;
	while (i < (int)command_line->dy_str->current_size)
	{
		if (command_line->dy_str->str[i] == '\\')
			backslashed = !backslashed;
		else if (command_line->dy_str->str[i] == '\'' && !backslashed)
			single_quoted = !single_quoted;
		else if (command_line->dy_str->str[i] == '\"' && !backslashed)
			double_quoted = !double_quoted;
		else if (command_line->dy_str->str[i] == '!'
				&& !backslashed && !single_quoted
				&& (i != (int)command_line->dy_str->current_size - 1
					&& !ft_iswhite(command_line->dy_str->str[i + 1])))
		{
			*expanded = 1;
			if ((ret = sh_history_expand(shell, command_line, &i,
				&double_quoted)) != SUCCESS)
			{
				return (ret);
			}
		}
		else
			backslashed = 0;
		i++;
	}
	return (SUCCESS);
}
