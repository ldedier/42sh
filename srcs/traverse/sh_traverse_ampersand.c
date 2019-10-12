/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_traverse_ampersand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:27:20 by jmartel           #+#    #+#             */
/*   Updated: 2019/10/11 11:08:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"

/*
** sh_traverse_ampersand :
** This function it's called when we find a semi_col in
** the t_list LIST (grammar)
** It take the context and the and_or node to execute.
*/

int		sh_traverse_ampersand(t_ast_node *node_to_execute, t_context *context)
{
	int 	ret;

	context->cmd_type |= BG_NODE;
	if (g_job_ctrl->interactive)
	{
		// if the seperator_op is "&" add the job now in background
		if ((ret = job_add(0)) != SUCCESS)
			return (ret);
		// Make sure we don't add another job at lower ast levels (simple command for example).
		g_job_ctrl->job_added = 1;
	}
	// if the shell is not interactive, and the seperator is "&"
	// We need the WNOHANG wait flag to make sure the shell does not wait for the command.
	context->wait_flags |= WNOHANG;
	// ft_dprintf(g_term_fd, "%swaitflag in AMPERSAND: %d%s\n", GREEN, context->wait_flags, EOC);
	ret = sh_traverse_and_or(node_to_execute, context);
	return (ret);
}
