/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/22 11:56:09 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

//<<<<<<< HEAD
//void		sh_execute_binary(t_ast_node *father_node, t_context *context)
////void		sh_execute_binary(t_context *context)
//{
//	int	res;
//
//	reset_signals();
//	if ((res = loop_traverse_redirection(father_node, context)) == SUCCESS)
//	{
//		execve(context->path, (char **)context->params->tbl,
//=======
static int		sh_no_slash_cmd(t_context *context)
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
		sh_env_update_ret_value(context->shell, SH_RET_CMD_NOT_FOUND);
		sh_perror_err(context->params->tbl[0], SH_ERR1_CMD_NOT_FOUND);
		return (SH_RET_CMD_NOT_FOUND);
	}
}

static int		sh_slash_cmd(t_context *context)
{
	if (!(context->path = ft_strdup(context->params->tbl[0])))
		return (sh_perror(SH_ERR1_MALLOC, "traverse_simple_command"));
	if (sh_traverse_sc_check_perm(context,
				context->params->tbl[0], context->params->tbl[0]) != SUCCESS)
		return (SH_RET_NO_PERM);
	return (SUCCESS);
}

void		sh_execute_binary(t_ast_node *father_node, t_context *context)
//void		sh_execute_binary(t_context *context)
{
	int		ret;

	reset_signals();
	// ft_dprintf(g_term_fd, "%sExecuting %s", GREEN, (char **)context->params->tbl[0]);
	// ft_dprintf(g_term_fd, "\tpid: %d, ppid: %d, pgid: %d%s\n",
	// 	getpid(), getppid(), getpgid(getpid()), EOC);

	if (!ft_strchr(context->params->tbl[0], '/'))
	{
		ret = sh_no_slash_cmd(context);
		if (ret != SUCCESS)
			exit(context->shell->ret_value);
	}
	else
	{
		ret = sh_slash_cmd(context);
		if (ret != SUCCESS)
			exit(context->shell->ret_value);
	}
	if ((ret = loop_traverse_redirection(father_node, context)) == SUCCESS)
	{
		execve(context->path, (char **)context->params->tbl,
				(char **)context->env->tbl);
			ret = SH_RET_NOT_EXECUTABLE;
			sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	}
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	exit(ret);
}
