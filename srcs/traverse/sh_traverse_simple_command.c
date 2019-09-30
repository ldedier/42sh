/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_simple_command.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:34:52 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/28 22:07:17 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

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

int		sh_traverse_simple_command(t_ast_node *node, t_context *context)
{
	int		ret;

	context->phase = E_TRAVERSE_PHASE_REDIRECTIONS;
	sh_traverse_tools_show_traverse_start(node, context);
	while (context->phase <= E_TRAVERSE_PHASE_EXECUTE)
	{
		if ((ret = sh_traverse_tools_browse(node, context)))
		{
			if (sh_reset_redirection(&(context->redirections)) != SUCCESS)
				return (FAILURE);
			return (ret);
		}
		context->phase += 1;
	}
	ret = sh_execute_simple_command(context);
	if (sh_reset_redirection(&(context->redirections)) != SUCCESS)
		return (FAILURE);
	if (!ret)
		ret = sh_env_save_restore(context);
	sh_traverse_tools_show_traverse_ret_value(node, context, ret);
	return (ret);
}
