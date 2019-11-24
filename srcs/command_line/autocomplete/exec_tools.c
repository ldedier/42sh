/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:35:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 15:20:37 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_free_turn_exec_autocompletion(t_exec *exec, int ret)
{
	free_execution_tools(&exec->tokens, &exec->ast_root, &exec->cst_root);
	free(exec->word.str);
	free(exec->word.to_compare);
	return (ret);
}

int		sh_free_turn_exec(t_exec *exec, int ret)
{
	free_execution_tools(&exec->tokens, &exec->ast_root, &exec->cst_root);
	return (ret);
}

void	init_exec(t_exec *exec)
{
	exec->ast_root = NULL;
	exec->cst_root = NULL;
}

void	init_exec_autocompletion(t_exec *exec)
{
	exec->ast_root = NULL;
	exec->cst_root = NULL;
	exec->word.token = NULL;
}
