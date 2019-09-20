/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 15:51:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"
#include "libft.h"
#include "sh_grammar.h"

// static int	add_first_process(t_context *context, pid_t pid, t_job *j)
// {
// 	t_process	*p;

// 	ft_printf("First process\n");
// 	if ((p = malloc(sizeof(t_process))) == NULL)
// 		return (FAILURE);
// 	p->pid = pid;
// 	p->completed = 0;
// 	p->stopped = 0;
// 	p->status = 0;
// 	p->argv = (char **)context->params->tbl;
// 	j->pgid = pid;
// 	j->first_process = p;
// 	return (SUCCESS);
// }

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

	ft_printf("Adding process ");
	str_tab_print((char **)context->params->tbl);
	ft_printf(" ");
	// create the process with the pid pid
	if ((new_p = process_create(context, pid)) == NULL)
		return (FAILURE);
	// iterate to the last job created (current job)
	j = g_job_ctrl->first_job;
	while (j->next != NULL)
		j = j->next;
	ft_printf("to the job number: %d\n", j->number);
	// if it's the first process in the current job, make it the process group leader
	if (j->first_process == NULL)
	{
		ft_printf("making the process \"");
		str_tab_print((char **)context->params->tbl);
		ft_printf("\" the group leader\n");
		j->first_process = new_p;
		// job_print();
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