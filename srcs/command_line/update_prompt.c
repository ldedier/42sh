/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:11 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 21:16:34 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			fill_prompt_command_mode(char **new_prompt,
			t_command_line *command_line)
{
	char *count_str;

	if (!(*new_prompt = ft_strjoin_free(*new_prompt, COMMAND_PROMPT, 1)))
		return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
	if (command_line->current_count->active)
	{
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, COUNT_PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
		if (!(count_str = ft_itoa(command_line->current_count->tmp_value)))
			return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, count_str, 1)))
		{
			free(count_str);
			return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
		}
		free(count_str);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, ")", 1)))
			return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
	}
	if (!(*new_prompt = ft_strjoin_free(*new_prompt, ")", 1)))
		return (sh_perror(SH_ERR1_MALLOC, "fill_prompt_command_mode"));
	return (SUCCESS);
}

int			update_prompt_mode(t_command_line *command_line, char **new_prompt)
{
	if (command_line->mode == E_MODE_VISUAL)
	{
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, VISUAL_PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->mode == E_MODE_COMMAND)
	{
		if (fill_prompt_command_mode(new_prompt, command_line) != SUCCESS)
			return (FAILURE);
	}
	else if (command_line->mode == E_MODE_REPLACE)
	{
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, REPLACE_PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	if (command_line->context != E_CONTEXT_STANDARD)
	{
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, PROMPT_SUFFIX, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	return (SUCCESS);
}

int			update_prompt(t_shell *shell, t_command_line *command_line)
{
	char	*new_prompt;

	command_line->prev_prompt_len = ft_strlen_utf8(command_line->prompt);
	ft_strdel(&command_line->prompt);
	if (update_prompt_context(shell, command_line, &new_prompt))
		return (FAILURE);
	if (update_prompt_mode(command_line, &new_prompt))
		return (FAILURE);
	if (!(new_prompt = ft_strjoin_free(new_prompt, " ", 1)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	command_line->prompt = new_prompt;
	return (SUCCESS);
}

int			update_prompt_from_quote(
	t_shell *shell, t_command_line *command_line, char quote, int backslash)
{
	if (backslash == 0)
	{
		if (quote == '\'')
			command_line->context = E_CONTEXT_QUOTE;
		else if (quote == '\"')
			command_line->context = E_CONTEXT_DQUOTE;
		else if (quote == '<')
			command_line->context = E_CONTEXT_PRCSUBST_IN;
		else if (quote == '>')
			command_line->context = E_CONTEXT_PRCSUBST_OUT;
		else if (quote == '(')
			command_line->context = E_CONTEXT_CMDSUBST;
		else if (quote == '{')
			command_line->context = E_CONTEXT_VARIABLE;
		else if (quote == '|')
			command_line->context = E_CONTEXT_PIPE;
	}
	else
		command_line->context = E_CONTEXT_BACKSLASH;
	return (update_prompt(shell, command_line));
}
