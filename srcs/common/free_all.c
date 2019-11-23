/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/23 03:03:45 by ldedier          ###   ########.fr       */
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
