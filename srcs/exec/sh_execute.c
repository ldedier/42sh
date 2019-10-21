/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:31:19 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/21 08:51:35 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

static int	sh_exec_binaire(t_ast_node *father_node, t_context *context)
{
	int			res;
	pid_t		child;
	(void)father_node;

	if (sh_pre_execution() != SUCCESS)
		return (FAILURE);
	if ((child = fork()) == -1)
		return (sh_perror(SH_ERR1_FORK, "sh_exec_binaire"));
	if (child == 0)
		sh_execute_binary(/*father_node,*/ context);
	else
	{
		waitpid(child, &res, 0);
		sh_env_update_ret_value_wait_result(context, res);
		if (sh_post_execution() != SUCCESS)
			return (FAILURE);
		g_glob.command_line.interrupted = WIFSIGNALED(res);
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int	sh_no_slash_cmd(t_context *context)
{
	if ((context->builtin = sh_builtin_find(context)))
		return (SUCCESS);
	if (sh_traverse_sc_search_in_hash(context) != SUCCESS)
	{
		if (sh_traverse_sc_search_in_path(context) == FAILURE)
			return (FAILURE);
	}
	if (context->path)
		return (SUCCESS);
	else
	{
		sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
		return (SH_RET_CMD_NOT_FOUND);
	}
}

static int	sh_slash_cmd(t_context *context)
{
	if (!(context->path = ft_strdup(context->params->tbl[0])))
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	if (sh_traverse_sc_check_perm(context,
				context->params->tbl[0], context->params->tbl[0]) != SUCCESS)
		return (SH_RET_NO_PERM);
	return (SUCCESS);
}

int 		sh_execute_simple_command(t_ast_node *father_node, t_context *context)
{
	int 	ret;

	ret = SUCCESS;
	if (!context->params->tbl || !context->params->tbl[0])
		return (SUCCESS);
	if (!ft_strchr(context->params->tbl[0], '/'))
		ret = sh_no_slash_cmd(context);
	else
		ret = sh_slash_cmd(context);
	if (ret == SUCCESS)
	{
		if (context->builtin)
			ret = sh_execute_builtin(father_node, context);
		else
			ret = sh_exec_binaire(father_node, context);
	}
	return (ret);
}
