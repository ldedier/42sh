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

void	free_execution_tools(t_list **tokens, t_ast_node **ast_root,
		t_ast_node **cst_root)
{
	sh_free_ast_node(ast_root, 0);
	sh_free_ast_node(cst_root, 0);
	ft_lstdel(tokens, sh_free_token_lst);
}

static int	sh_process_command(t_shell *shell, char *command)
{
	t_list		*tokens;
	int			ret;
	t_ast_node	*ast_root;
	t_ast_node	*cst_root;

	ast_root = NULL;
	cst_root = NULL;
	tokens = NULL;
	sh_verbose_update(shell);
	ret = 0;
	if ((ret = sh_lexer(command, &tokens, shell, E_LEX_STANDARD)) != SUCCESS)
	{
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = FAILURE;
	}
	if (!ret && (ret = sh_parser(shell, &tokens, &ast_root, &cst_root)))
	{
		sh_perror_err("syntax error", NULL);
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = FAILURE;
	}
	if (!ret)
		ret = sh_process_traverse(shell, ast_root);
	free_execution_tools(&tokens, &ast_root, &cst_root);
	return (ret);
}

int		execute_command(t_shell *shell, char *command, int should_add)
{
	int ret;

	shell->history.should_add = should_add;
	ret = sh_process_command(shell, command);
	if (ret == SUCCESS && shell->history.should_add)
		return (sh_append_to_history(&shell->history, command, 1));
	else
		return (ret);
}
