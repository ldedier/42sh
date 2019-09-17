/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/17 19:06:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

void		sh_close_all_other_contexts(t_context *context, t_list *contexts)
{
	t_context	*current_context;
	t_list		*ptr;

	ptr = contexts;
	while (ptr != NULL)
	{
		current_context = (t_context *)ptr->content;
		if (current_context != context)
			sh_process_execute_close_pipes(current_context);
		ptr = ptr->next;
	}
}

void		sh_execute_child_builtin(t_context *context, t_list *contexts)
{
	int ret;

	sh_process_execute_dup_pipes(context);
	// reset_signals();
	sh_close_all_other_contexts(context, contexts);
	ret = context->builtin(context);
	if (context->shell->ret_value_set)
		ret = context->shell->ret_value;
	sh_free_all(context->shell);
	// init_signals();	//	CHECK!!
	exit(ret);
}

void		sh_execute_child_binary(t_context *context, t_list *contexts)
{
	sh_process_execute_dup_pipes(context);
	reset_signals();
	sh_close_all_other_contexts(context, contexts);
	ft_printf("Executing Job #%d->\t\"%s\" with: pid: %d\tppid: %d\tpgid: %d\n",
		g_job_control->current_job->number	, context->path,
		getpid(), getppid(), getpgid(getpid()));
	tcsetpgrp (g_job_control->term_fd, g_job_control->current_job->pgid);
	pid_t grp = tcgetpgrp(0);
	ft_printf("CONTROLLING GROUP: %d (%d)\n",
		g_job_control->current_job->pgid, grp);
	execve(context->path, (char **)context->params->tbl,
			(char **)context->env->tbl);
	sh_perror(((char**)context->params->tbl)[0], SH_ERR1_EXECVE_FAIL);
	sh_process_execute_close_pipes(context);
	exit(SH_RET_NOT_EXECUTABLE);
}

void		sh_execute_child(t_context *context, t_list *contexts)
{
	if (context->builtin)
		sh_execute_child_builtin(context, contexts);
	else
		sh_execute_child_binary(context, contexts);
}
