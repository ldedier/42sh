/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 00:39:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/08/10 11:42:10 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** case: simple command (no pipes, no builtins)
*/
int			sh_process_process_execute(t_context *context)
{
	int			res;

	if (sh_pre_execution(context) != SUCCESS)
		return (FAILURE);
	if ((g_parent = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_process_process_execute"));
	if (g_parent == 0)
		sh_execute_child_binary(context, NULL);
	else
	{
		wait(&res);
		g_parent = 0;
		sh_env_update_ret_value_wait_result(context, res);
		sh_process_execute_close_pipes(context);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
	}
	return (SUCCESS);
}

int			sh_add_to_pipe_sequence(t_context *context)
{
	t_context	*context_dup;

	context->current_pipe_sequence_node
		->metadata.pipe_metadata.last_ret_value = 0;
	if (!(context_dup = t_context_dup(context)))
		return (FAILURE);
	if (ft_lstaddnew_ptr_last(&context->current_pipe_sequence_node->
		metadata.pipe_metadata.contexts, context_dup,
			sizeof(t_context)))
		return (FAILURE);
	return (SUCCESS);
}

int			sh_process_execute(t_context *context)
{
	if (context->current_pipe_sequence_node)
		return (sh_add_to_pipe_sequence(context));
	else
		return (sh_process_process_execute(context));
}
