/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:08:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/26 08:46:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		free_execution_tools(t_list **tokens, t_ast_node **ast_root,
		t_ast_node **cst_root)
{
	sh_free_ast_node(cst_root, 0);
	sh_free_ast_node(ast_root, 0);
	ft_lstdel(tokens, sh_free_token_lst);
}

static int	sh_process_command_parse_error(t_shell *shell, int ret, t_exec *res)
{
	sh_perror_err("syntax error", NULL);
	if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
		ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (2)");
	ft_lstdel(&res->tokens, sh_free_token_lst);
	if (!isatty(0))
		shell->running = 0;
	return (ret);
}

static int	sh_process_command(t_shell *shell, char *command)
{
	int			ret;
	t_exec		res;

	res.ast_root = NULL;
	res.cst_root = NULL;
	res.tokens = NULL;
	sh_verbose_update(shell);
	if ((ret = sh_lexer(command, &res.tokens, shell, E_LEX_STANDARD)))
	{
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (1)");
		ft_lstdel(&res.tokens, sh_free_token_lst);
	}
	else if ((ret = sh_parser(shell, &shell->parser, &res)))
		ret = sh_process_command_parse_error(shell, ret, &res);
	else
	{
		shell->exec = &res;
		ret = sh_process_traverse(shell, res.ast_root);
		free_execution_tools(&res.tokens, &res.ast_root, &res.cst_root);
	}
	return (ret);
}

int			execute_command(t_shell *shell, char *command, int should_add)
{
	int		ret;
	char	*dup;

	dup = NULL;
	shell->history.should_add = 1;
	if (should_add && !(dup = ft_strdup(command)))
		return (sh_perror(SH_ERR1_MALLOC, "execute_command"));
	shell->hist_dup = dup;
	ret = sh_process_command(shell, command);
	if (ret != FAILURE && should_add
		&& shell->history.should_add && !ft_iswhite_only(command))
	{
		ret = sh_append_to_history(&shell->history, dup, 1);
		ft_strdel(&dup);
		return (ret);
	}
	else
	{
		ft_strdel(&dup);
		return (ret);
	}
}
