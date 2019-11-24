/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_prompt_context.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:00:34 by jmartel           #+#    #+#             */
/*   Updated: 2019/11/24 21:18:02 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	update_prompt_context_check_ret(char **new_prompt)
{
	if (!*new_prompt)
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
		*new_prompt = ft_strjoin_free(*new_prompt, PROMPT, 1);
	}
	else if (command_line->context == E_CONTEXT_HEREDOC)
		*new_prompt = ft_strdup(HEREDOC_PROMPT);
	else if (command_line->context == E_CONTEXT_QUOTE)
		*new_prompt = ft_strdup(QUOTE_PROMPT);
	else if (command_line->context == E_CONTEXT_DQUOTE)
		*new_prompt = ft_strdup(DQUOTE_PROMPT);
	else if (command_line->context == E_CONTEXT_PIPE)
		*new_prompt = ft_strdup(PIPE_PROMPT);
	else if (command_line->context == E_CONTEXT_PRCSUBST_OUT
		|| command_line->context == E_CONTEXT_PRCSUBST_IN)
		*new_prompt = ft_strdup(PROCSUBST_PROMPT);
	else if (command_line->context == E_CONTEXT_CMDSUBST)
		*new_prompt = ft_strdup(CMDSUBST_PROMPT);
	else if (command_line->context == E_CONTEXT_VARIABLE)
		*new_prompt = ft_strdup(VARIABLE_PROMPT);
	else
		*new_prompt = ft_strdup(BACKSLASH_PROMPT);
	return (update_prompt_context_check_ret(new_prompt));
}
