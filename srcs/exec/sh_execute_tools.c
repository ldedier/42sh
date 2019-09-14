/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 11:14:49 by ldedier           #+#    #+#             */
/*   Updated: 2019/09/14 22:16:32 by mdaoud           ###   ########.fr       */
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

	// process_add(context, 0);
	// ft_printf("Executing builtin: %s, pid: %d, ppid: %d, pgid: %d\n", context->path, getpid(), getppid(),getpgid(getpid()));
	sh_process_execute_dup_pipes(context);
	reset_signals();
	sh_close_all_other_contexts(context, contexts);
	ret = context->builtin(context);
	if (context->shell->ret_value_set)
		ret = context->shell->ret_value;
	sh_free_all(context->shell);
	exit(ret);
}

void		sh_execute_child_binary(t_context *context, t_list *contexts)
{
	sh_process_execute_dup_pipes(context);
	reset_signals();
	sh_close_all_other_contexts(context, contexts);
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
