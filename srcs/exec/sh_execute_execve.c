/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_execve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:52:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/16 15:48:38 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void		sh_execute_execve(t_ast_node *father_node, t_context *context)
{
	int		ret;

	reset_signals();
	if ((ret = loop_traverse_redirection(father_node, context)) == SUCCESS)
	{
		if (!context->params->tbl || !context->params->tbl[0])
			exit(SUCCESS);
		if (context->path == NULL)
		{
			sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
			exit(SH_RET_CMD_NOT_FOUND);
		}
		if ((ret = sh_traverse_sc_check_perm(context,
					context->path, context->path)) != SUCCESS)
		{
			sh_env_update_ret_value(context->shell, ret);
			exit(context->shell->ret_value);
		}
		close(g_term_fd);
		execve(context->path, (char **)context->params->tbl,
				(char **)context->env->tbl);
		ret = SH_RET_NOT_EXECUTABLE;
		sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	}
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	exit(ret);
}
