/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/20 12:54:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

static int	get_cmd_string(t_ast_node *node, t_context *context)
{
	char		*tmp;
	t_symbol_id	id;

	tmp = NULL;
	id = node->symbol->id;
	if ((g_grammar[id].get_job_string(node, &tmp)) != SUCCESS)
		return (ERROR);
	context->cmd_string = tmp;
	return (SUCCESS);
}

/*
** sh_traverse_simple_command
** Search and apply redirection, then try to execute command calling
** sh_execute_redirection.
** After the execution call, doesn't matter if it succeed or not,
** we undo fd redirection.
**
** return  :
**	FAILURE : malloc error or issue with dup2
**	any value returned by a builtin executed or a process launched
*/

long		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret;

	get_cmd_string(node, context);
	context->phase = E_TRAVERSE_PHASE_EXPANSIONS;
	sh_traverse_tools_show_traverse_start(node, context);
	while (context->phase <= E_TRAVERSE_PHASE_EXECUTE)
	{
		if ((ret = sh_traverse_tools_browse(node, context)))
		{
			free(context->cmd_string);
			if (sh_reset_redirection(&(context->redirections)) != SUCCESS)
				return (FAILURE);
			return (ret);
		}
		context->phase += 1;
	}
	ret = sh_execute_simple_command(node, context);
	free(context->cmd_string);
	context->cmd_string = NULL;
	if (sh_reset_redirection(&(context->redirections)) != SUCCESS)
		return (FAILURE);
	if (!ret)
		ret = sh_env_save_restore(context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
