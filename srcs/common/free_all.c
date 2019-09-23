/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:27:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/02 15:08:46 by ldedier          ###   ########.fr       */
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

void	free_file_dlst(void *f, size_t dummy)
{
	(void)dummy;
	free_file((t_file *)f);
}

void	free_entry_dlst(void *e, size_t dummy)
{
	(void)dummy;
	t_entry_free((t_entry *)e);
}

void	sh_free_all(t_shell *shell)
{
	sh_free_parser(&shell->parser);
	sh_free_command_line(&g_glob.command_line);
	ft_dlstdel(&shell->history.commands, free_entry_dlst);
	if (shell->vars)
		ft_dy_tab_del(shell->vars);
	if (shell->env)
		ft_dy_tab_del(shell->env);
	if (shell->binaries)
		ft_hash_table_del(shell->binaries, sh_free_binary_lst);
}
