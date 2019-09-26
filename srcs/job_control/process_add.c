/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/26 01:52:50 by mdaoud           ###   ########.fr       */
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
	p->argv = str_tab_duplicate((char **)context->params->tbl);
	// p->argv = (char **)context->params->tbl;
	p->next = NULL;
	return (p);
}

int			process_add(t_context *context, pid_t pid)
{
	t_job		*j;		//	current job
	t_process	*p;		//	process iterator
	t_process	*new_p;	//	the newly created process

	// ft_printf("Adding process ");
	// str_tab_print((char **)context->params->tbl);
	// ft_printf(" ");
	// create the process with the pid pid
	if ((new_p = process_create(context, pid)) == NULL)
		return (FAILURE);
	// Go to the last job
	j = g_job_ctrl->curr_job;
	// ft_printf("to the job number: %d\n", j->number);
	// if it's the first process in the current job, make it the process group leader
	if (j->first_process == NULL)
	{
		// ft_printf("First process\n");
		// str_tab_print((char **)context->params->tbl);
		j->first_process = new_p;
		return (SUCCESS);
	}
	// if not, append it to the process list (to be the last process)
	p = j->first_process;
	while (p->next != NULL)
		p = p->next;
	p->next = new_p;
	// job_print();
	return (SUCCESS);
}