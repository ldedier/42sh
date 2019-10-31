/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/31 17:38:32 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void		sh_execute_execve(t_ast_node *father_node, t_context *context)
{
	int		ret;

	reset_signals();
	close(g_term_fd);//need to close tty to not duplicate if we call ./42sh from a ./42sh
	if ((ret = loop_traverse_redirection(father_node, context)) == SUCCESS)
	{
		if (context->path == NULL)
		{
			sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
			exit(SH_RET_CMD_NOT_FOUND);
		}
		if (sh_traverse_sc_check_perm(context,
					context->path, context->path) != SUCCESS)
			exit(SH_RET_NO_PERM);
		execve(context->path, (char **)context->params->tbl,
				(char **)context->env->tbl);
			ret = SH_RET_NOT_EXECUTABLE;
			sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	}
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	exit(ret);
}
