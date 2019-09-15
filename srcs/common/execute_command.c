/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:08:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/15 16:08:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	sh_process_command(t_shell *shell, char *command)
{
	t_list  *tokens;
	int     ret;

	sh_verbose_update(shell);
	ret = 0;
	if ((ret = sh_lexer(command, &tokens, shell, E_LEX_STANDARD)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = FAILURE;
	}
	if (!ret && (ret = sh_parser(tokens, shell)))
	{
		sh_perror_err("syntax error", NULL);
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = FAILURE;
	}
	if (!ret)
		ret = sh_process_traverse(shell);
	sh_clear_parser(&shell->parser);
	return (ret);
}

int		execute_command(t_shell *shell, char *command)
{
	int ret;

	shell->history.should_add = 1;
	ret = sh_process_command(shell, command);
	if (ret == SUCCESS && shell->history.should_add)
		return (sh_append_to_history(&shell->history, command, 1));
	else
		return (ret);
}
