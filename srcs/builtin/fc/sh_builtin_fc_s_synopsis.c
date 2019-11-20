/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_fc_s_synopsis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:46:05 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/17 15:39:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static void		fill_finder(t_fc_operand **finder,
	t_fc_options *opts, char **substitution_str)
{
	if (!opts->from.parsed)
	{
		opts->from.un.integer = -1;
		opts->from.type = E_FC_INTEGER;
		opts->from.parsed = 1;
		*finder = &opts->from;
	}
	else if (opts->from.type == E_FC_STRING
			&& ft_strchr(opts->from.un.string, '=') && !opts->to.parsed)
	{
		opts->to.un.integer = -1;
		opts->to.type = E_FC_INTEGER;
		opts->to.parsed = 1;
		*substitution_str = opts->from.un.string;
		*finder = &opts->to;
	}
	else
		*finder = &opts->from;
}

int				sh_builtin_fc_s_synopsis(t_context *context, t_fc_options *opts)
{
	t_dlist			*entry_ptr;
	t_fc_operand	*finder;
	char			*substitution_str;
	char			*res;
	t_entry			*entry;

	context->shell->history.should_add = 0;
	if (context->shell->exec_depth++ >= MAX_EXEC_RECURSIONS)
		return (sh_perror_err(SH_ERR1_MAX_RECUR, "sh_builtin_fc_s_synopsis"));
	substitution_str = NULL;
	fill_finder(&finder, opts, &substitution_str);
	if (!(entry_ptr =
		get_entry_from_fc_operand(&context->shell->history, finder, 1)))
		return (sh_perror_err(SH_BLT_NO_CMD_FOUND, NULL));
	entry = entry_ptr->content;
	if (!(res = get_command_to_execute_fc(entry->command, substitution_str)))
		return (sh_perror(SH_ERR1_MALLOC, "sh_builtin_fc_s_synopsis"));
	ft_dprintf(2, "%s\n", res);
	execute_command(context->shell, res, 1);
	free(res);
	context->shell->history.should_add = 0;
	return (SUCCESS);
}
