/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:08:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/01 21:18:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	free_execution_tools(t_list **tokens, t_ast_node **ast_root,
		t_ast_node **cst_root)
{
	sh_free_ast_node(cst_root, 0);
	sh_free_ast_node(ast_root, 0);
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
			ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (1)");
		ft_lstdel(&tokens, sh_free_token_lst);
	}
	else if ((ret = sh_parser(shell, &tokens, &ast_root, &cst_root)))
	{
		sh_perror_err("syntax error", NULL);
		if (sh_env_update_ret_value_and_question(shell, ret) == FAILURE)
			ret = sh_perror(SH_ERR1_MALLOC, "sh_process_command (2)");
		ft_lstdel(&tokens, sh_free_token_lst);
	}
	else
	{
		ret = sh_process_traverse(shell, ast_root);
		free_execution_tools(&tokens, &ast_root, &cst_root);
	}
	return (ret);
}

int		execute_command(t_shell *shell, char *command, int should_add)
{
	int		ret;
	char	*dup;

	dup = NULL;
	shell->history.should_add = 1;
	if (should_add && !(dup = ft_strdup(command)))
		return (sh_perror(SH_ERR1_MALLOC, "execute_command"));
	ret = sh_process_command(shell, command);
	if (ret != FAILURE && should_add && shell->history.should_add)
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
