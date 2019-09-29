/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/29 17:40:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"
#include "libft.h"
#include "sh_grammar.h"

t_process	*process_create(t_context *context, pid_t pid)
{
	t_process	*p;

	if ((p = malloc(sizeof(t_process))) == NULL)
		return (NULL);
	p->pid = pid;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
	p->next = NULL;
	if (context != NULL)
	{
		p->argv = str_tab_duplicate((char **)context->params->tbl);
		if (p->argv == NULL)
			return (NULL);
	}
	// p->argv = (char **)context->params->tbl;
	return (p);
}

int			process_add(t_context *context, pid_t pid)
{
	t_job		*j;		//	current job
	t_process	*p;		//	process iterator
	t_process	*new_p;	//	the newly created process

	// create the process with the pid pid
	if ((new_p = process_create(context, pid)) == NULL)
		return (jc_error_free(SH_ERR1_MALLOC, "process_add", 1, FAILURE));
	// Go to the last job
	j = g_job_ctrl->curr_job;
	// if it's the first process in the current job, make it the process group leader
	if (j->first_process == NULL)
	{
		j->first_process = new_p;
		return (SUCCESS);
	}
	// if not, append it to the process list (to be the last process)
	p = j->first_process;
	while (p->next != NULL)
	{
		if (p->pid == pid)
			return (SUCCESS);
		p = p->next;
	}
	p->next = new_p;
	return (SUCCESS);
}
