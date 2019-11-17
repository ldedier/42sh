/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_default_synopsis.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:47:47 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:24:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

int			sh_builtin_fc_fill_text(t_history *history,
	t_dlist *from, t_dlist *to)
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

char		*sh_get_editor(char *editor, t_shell *shell)
{
	char *fcedit_var;

	if (editor)
		return (ft_strdup(editor));
	else
	{
		if ((fcedit_var = sh_vars_get_value(shell->env, shell->vars, "FCEDIT")))
			return (ft_strdup(fcedit_var));
		else
			return (ft_strdup("ed"));
	}
}

void		fill_default_opts_default_synopsis(t_fc_options *opts)
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

int			sh_execute_editor(char *editor, t_shell *shell)
{
	char *command;

	if (!(command = ft_strjoin_3(editor, " ", EDIT_FILE)))
		return (FAILURE);
	if (execute_command(shell, command, 0) == FAILURE)
	{
		free(command);
		return (FAILURE);
	}
	free(command);
	return (SUCCESS);
}

int			sh_builtin_fc_default_synopsis(t_context *context,
	t_fc_options *opts)
{
	t_dlist *from;
	t_dlist *to;
	int		ret;

	fill_default_opts_default_synopsis(opts);
	if (!(from =
		get_entry_from_fc_operand(&context->shell->history, &opts->from, 1)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (!(to = get_entry_from_fc_operand(&context->shell->history,
		&opts->to, 1)))
		return (sh_perror_err(SH_BLT_HISTORY_RANGE, NULL));
	if (opts->opt_r)
		swap_entries(&context->shell->history, &from, &to);
	if (sh_builtin_fc_fill_text(&context->shell->history, from, to))
		return (FAILURE);
	if (!(opts->editor = sh_get_editor(opts->editor, context->shell)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_fc_default_synopsis"));
	ft_printf("%s\n", opts->editor);
	if (sh_execute_editor(opts->editor, context->shell) != SUCCESS)
		return (ft_free_turn(opts->editor, FAILURE));
	free(opts->editor);
	ret = sh_execute_commands_from_file(context->shell, EDIT_FILE);
	context->shell->history.should_add = 0;
	return (ret);
}
