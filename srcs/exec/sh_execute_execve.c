/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_execve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:52:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/09 23:54:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"


static int	call_execve(t_context *context)
{
	int	ret;
	
	ret = SUCCESS;
	if (context->path == NULL)
	{
		sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
		ret = SH_RET_CMD_NOT_FOUND;
	}
	else if (sh_traverse_sc_check_perm(context,
				context->path, context->path) != SUCCESS)
	{
		free(context->path);
		ret = context->shell->ret_value;
	}
	else
	{
		execve(context->path, (char **)context->params->tbl,
				(char **)context->env->tbl);
		sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
		ret = SH_RET_NOT_EXECUTABLE;
	}
	return (ret);
}

void		sh_execute_execve(t_ast_node *father_node, t_context *context)
{
	int		ret;

	reset_signals();
	close(g_term_fd);
	if ((ret = loop_traverse_redirection(father_node, context)) == SUCCESS)
		ret = call_execve(context);
	sh_reset_redirection(&context->redirections);
	free(context->cmd_string);
	sh_free_all(context->shell);
	exit(ret);
}
