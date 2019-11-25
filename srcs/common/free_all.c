/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/24 16:17:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

void	sh_free_binary(t_binary *binary)
{
	free(binary->name);
	free(binary->path);
	free(binary);
}

void	sh_free_binary_lst(void *b, size_t dummy)
{
	(void)dummy;
	sh_free_binary((t_binary *)b);
}

void	free_file(t_file *file)
{
	free(file->name);
	free(file->fullname);
	free(file);
}

void	free_ast_tools(t_context *context, int free_choice)
{
	if (free_choice & 1)
	{
		sh_free_ast_node(&context->shell->exec->ast_root, 0);
		sh_free_ast_node(&context->shell->exec->cst_root, 0);
		ft_lstdel(&context->shell->exec->tokens, sh_free_token_lst);
		free_choice &= ~1;
	}
	if (free_choice & 2)
	{
		ft_strdel(&context->shell->hist_cmd);
		free_choice &= ~2;
	}
	if (free_choice & 4)
	{
		t_context_free_content(context);
		free_choice &= ~4;
	}
	if (free_choice & 8)
	{
		ft_strdel(&context->cmd_string);
		free_choice &= ~8;
	}
	// if (free_choice & 16 && IS_PIPE(context->cmd_type))
	if (IS_PIPE(context->cmd_type))
	// if (g_job_ctrl->to_free & 16)
	{
		free(context->shell->pipe->tab_pds);
		context->shell->pipe->tab_pds = NULL;
		free(context->shell->pipe->tab_pid);
		context->shell->pipe->tab_pid = NULL;
		g_job_ctrl->to_free &= ~16;
	}
}

void	sh_free_all(t_shell *shell)
{
	job_control_free();
	sh_free_parser(&shell->parser);
	sh_free_parser(&shell->parser_ar);
	sh_free_command_line(&g_glob.command_line);
	ft_dlstdel(&shell->history.commands, free_entry_dlst);
	if (shell->vars)
		ft_dy_tab_del_ptr(shell->vars);
	if (shell->env)
		ft_dy_tab_del_ptr(shell->env);
	if (shell->saved_env)
		ft_dy_tab_del_ptr(shell->saved_env);
	if (shell->alias)
		ft_dy_tab_del_ptr(shell->alias);
	if (shell->binaries)
		ft_hash_table_del(shell->binaries, sh_free_binary_lst);
}
