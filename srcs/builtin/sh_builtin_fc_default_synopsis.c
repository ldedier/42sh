/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_default_synopsis.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:47:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/20 12:48:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int		sh_builtin_fc_fill_text(t_history *history, t_dlist *from, t_dlist *to)
{
	int		list_way;
	t_dlist	*ptr;
	int		fd;

	if ((fd = open(EDIT_FILE, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
		return (sh_perror(SH_ERR1_EDIT, "sh_builtin_fc_fill_text"));
	list_way = get_listing_way(history, from, to);
	ptr = from;
	if (from == to)
		ft_dprintf(fd, "%s\n", ((t_entry *)ptr->content)->command);
	while (ptr != to)
	{
		ft_dprintf(fd, "%s\n", ((t_entry *)ptr->content)->command);
		if (list_way < 0)
			ptr = ptr->next;
		else
			ptr = ptr->prev;
	}
	if (to != from)
		ft_dprintf(fd, "%s\n", ((t_entry *)ptr->content)->command);
	close(fd);
	return (0);
}

char	*sh_get_editor(char *editor, t_shell *shell)
{
	char *fcedit_var;

	if (editor)
		return (ft_strdup(editor));
	else
	{
		if ((fcedit_var = sh_vars_get_value(NULL, shell->vars, "FC_EDIT")))
			return (ft_strdup(fcedit_var));
		else
			return (ft_strdup("ed"));
	}
}

void	fill_default_opts_default_synopsis(t_fc_options *opts)
{
	if (!opts->from.parsed)
	{
		opts->from.un.integer = -1;
		opts->from.type = E_FC_INTEGER;
	}
	if (!opts->to.parsed)
	{
		opts->to.un.integer = opts->from.un.integer;
		opts->to.type = E_FC_INTEGER;
	}
}

int		sh_execute_editor(char *editor, t_shell *shell)
{
	char *command;

	if (!(command = ft_strjoin_3(editor, " ", EDIT_FILE)))
		return (FAILURE);
	if (execute_command(shell, command, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


static int      sh_process_read_canonical_gnl(t_shell *shell, t_gnl_info *info)
{
	int ret;

	if (info->separator != E_SEPARATOR_ZERO)
	{
		if ((ret = execute_command(shell, info->line, 1)))
		{
			free(info->line);
			return (ret);
		}
	}
	else
	{
		free(info->line);
		return (sh_perror("Illegal characters received from input",
					"sh_process_read_canonical_gnl"));
	}
	free(info->line);
	return (ret);
}

int		sh_execute_commands_from_file(t_shell *shell, char *filename)
{
	int         gnl_ret;
	t_gnl_info  info;
	int         ret;
	int			fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (sh_perror(SH_ERR1_EDIT, "sh_execute_commands_from_edit_file"));
	ret = SUCCESS;
	while (shell->running && (gnl_ret = get_next_line2(fd, &info, 1)) == 1)
	{
		if ((ret = sh_process_read_canonical_gnl(shell, &info)))
		{
			close(fd);
			return (ret);
		}
	}
	if (gnl_ret == -1)
	{
		close(fd);
		return (sh_perror("get_next_line error",
			"sh_execute_commands_from_edit_file"));
	}
	if (shell->running)
		free(info.line);
	close(fd);
	return (ret);
}

int		sh_builtin_fc_default_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist *from;
	t_dlist *to;

	fill_default_opts_default_synopsis(opts);
	if (!(from
		= get_entry_from_fc_operand(&context->shell->history, &opts->from)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (!(to = get_entry_from_fc_operand(&context->shell->history, &opts->to)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (opts->opt_r)
		swap_entries(&context->shell->history, &from, &to);
	if (sh_builtin_fc_fill_text(&context->shell->history, from, to))
		return (FAILURE);
	if (!(opts->editor = sh_get_editor(opts->editor, context->shell)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_fc_default_synopsis"));
	if (sh_execute_editor(opts->editor, context->shell) != SUCCESS)
	{
		free(opts->editor);
		return (FAILURE);
	}
	free(opts->editor);
	return (sh_execute_commands_from_file(context->shell, EDIT_FILE));
}
