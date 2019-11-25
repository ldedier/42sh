/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_execve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:52:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/24 15:44:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int	call_execve(t_context *context)
{
	int		ret;

	ret = SUCCESS;
	if (!context->params->tbl || !context->params->tbl[0])
		return (context->shell->ret_value);
	if (context->path == NULL)
	{
		sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
		return (SH_RET_CMD_NOT_FOUND);
	}
	if ((ret = sh_traverse_sc_check_perm(context,
				context->path, context->path)) != SUCCESS)
	{
		sh_env_update_ret_value(context->shell, ret);
		return (context->shell->ret_value);
	}
	close(g_term_fd);
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	ret = SH_RET_NOT_EXECUTABLE;
	sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	return (ret);
}

void		sh_execute_execve(t_ast_node *parent_node, t_context *context)
{
	int		ret;

	reset_signals();
	ret = SUCCESS;
	if ((ret = loop_traverse_redirection(parent_node, context)) == SUCCESS)
		ret = call_execve(context);
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	free_ast_tools(context, 31);
	exit(ret);
}
