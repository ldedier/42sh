/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_execve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:52:40 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/11/21 19:34:59 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int	sh_call_execve(t_context *context)
{
	char	*path;
	char	**tbl;
	char	**env;

	path = context->path;
	tbl = (char **)context->params->tbl;
	env = (char **)context->env->tbl;
	execve(path, tbl, env);
	sh_perror(tbl[0], SH_ERR1_EXECVE_FAIL);
	return (SH_RET_NOT_EXECUTABLE);
}

static void	sh_check_cmd_name(t_context *context)
{
	int	ret;

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
}

void		sh_execute_execve(t_ast_node *father_node, t_context *context)
{
	int		ret;

	reset_signals();
	ret = SUCCESS;
	context->is_builtin = 0;
	if ((ret = loop_traverse_redirection(father_node, context)) == SUCCESS)
	{
		sh_check_cmd_name(context);
		close(g_term_fd);
		ret = sh_call_execve(context);
	}
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	exit(ret);
}
