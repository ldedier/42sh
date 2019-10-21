/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/10/21 08:48:52 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

//void		sh_execute_binary(t_ast_node *father_node, t_context *context)
void		sh_execute_binary(t_context *context)
{
	int	res;

//	if ((res = loop_traverse_redirection(father_node, context)) == SUCCESS)
//	{
		reset_signals();
		execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
		res = SH_RET_NOT_EXECUTABLE;
		sh_perror(((char **)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
//	}
	sh_reset_redirection(&context->redirections);
	sh_free_all(context->shell);
	exit(res);
}
