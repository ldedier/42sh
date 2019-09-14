/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/12 14:59:11 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_sc_no_slash_cmd:
**	Function launching the execution of a process if context->params->tbl[0]
**	do not contain a path (does not contain a '/' character)
**	It try to launch any builtin, then look in $PATH env variable.
**	If any command was found it is launched
**	(Final else return SUCCESS to let cmd || cmd works)
**
** return  :
**	FAILURE : malloc error
**	ERROR : command not found
**	any value returned by a builtin executed or a process launched
*/

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret = SUCCESS;
	int 	phase;

	// phase = E_TRAVERSE_PHASE_EXPANSIONS;
	phase = E_TRAVERSE_PHASE_EXECUTE;
	sh_traverse_tools_show_traverse_start(node, context);
	while (phase <= E_TRAVERSE_PHASE_EXECUTE)
	{
		context->phase = phase;
		if ((ret = sh_traverse_tools_browse(node, context)))
			return (ret);
		phase++;
	}
	if (sh_env_save(context) == FAILURE)
		return (FAILURE);
	sh_env_save_delete_exported(context);
	ret = sh_execute_simple_command(context);
	if (sh_env_save_restore(context) == FAILURE)
		return (FAILURE);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
