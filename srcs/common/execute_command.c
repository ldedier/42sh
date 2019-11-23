/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:08:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/23 15:21:36 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void		free_execution_tools(t_list **tokens, t_ast_node **ast_root,
		t_ast_node **cst_root)
{
	if (tokens && *tokens)
		ft_lstdel(tokens, sh_free_token_lst);
	if (ast_root && *ast_root)
		sh_free_ast_node(ast_root, 0);
	if (cst_root && *cst_root)
		sh_free_ast_node(cst_root, 0);
}


static int	sh_process_command(t_shell *shell, char *command)
{
	int			ret;
	
	if (shell->exec == NULL)
		ft_dprintf(g_term_fd, RED"shell->exec is NULL\n"EOC);
	// else if (shell->exec->ast_root == NULL)
	// 	ft_dprintf(g_term_fd, RED"shell->exec->ast is NULL\n"EOC);
	shell->exec->ast_root = NULL;
	shell->exec->cst_root = NULL;
	shell->exec->tokens = NULL;
	sh_verbose_update(shell);
	ret = 0;
	if ((ret = sh_lexer(command, &shell->exec->tokens, shell, E_LEX_STANDARD)))
	{
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (1)");
		ft_lstdel(&shell->exec->tokens, sh_free_token_lst);
	}
	else if ((ret = sh_parser(shell, &shell->parser, shell->exec)))
	{
		sh_perror_err("syntax error", NULL);
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (2)");
		ft_lstdel(&shell->exec->tokens, sh_free_token_lst);
		if (!isatty(0))
			shell->running = 0;
	}
	else
	{
		ret = sh_process_traverse(shell, shell->exec->ast_root);
		// free_execution_tools(&shell->exec->tokens, &shell->exec->ast_root, &shell->exec->cst_root);
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
	shell->cmd_dup = dup;
	ret = sh_process_command(shell, command);
	if (ret != FAILURE && should_add && shell->history.should_add)
	{
		ret = sh_append_to_history(&shell->history, dup, 1);
		// ft_strdel(&dup);
		return (ret);
	}
	else
	{
		// ft_strdel(&dup);
		return (ret);
	}
}
