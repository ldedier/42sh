/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt_context.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:00:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 21:01:54 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	update_prompt_context_exp(
	t_command_line *command_line, char **new_prompt)
{
	if (command_line->context == E_CONTEXT_PIPE)
	{
		if (!(*new_prompt = ft_strdup(PIPE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_PRCSUBST_OUT
		|| command_line->context == E_CONTEXT_PRCSUBST_IN)
	{
		if (!(*new_prompt = ft_strdup(PROCSUBST_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_CMDSUBST)
	{
		if (!(*new_prompt = ft_strdup(CMDSUBST_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_VARIABLE)
	{
		if (!(*new_prompt = ft_strdup(VARIABLE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (!(*new_prompt = ft_strdup(BACKSLASH_PROMPT)))
		return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	return (SUCCESS);
}

int			update_prompt_context(
	t_shell *shell, t_command_line *command_line, char **new_prompt)
{
	if (command_line->context == E_CONTEXT_STANDARD)
	{
		if (update_prompt_cwd(shell, new_prompt))
			return (1);
		if (!(*new_prompt = ft_strjoin_free(*new_prompt, PROMPT, 1)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_HEREDOC)
	{
		if (!(*new_prompt = ft_strdup(HEREDOC_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_QUOTE)
	{
		if (!(*new_prompt = ft_strdup(QUOTE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	else if (command_line->context == E_CONTEXT_DQUOTE)
	{
		if (!(*new_prompt = ft_strdup(DQUOTE_PROMPT)))
			return (sh_perror(SH_ERR1_MALLOC, "update_prompt"));
	}
	return (update_prompt_context_exp(command_line, new_prompt));
}
