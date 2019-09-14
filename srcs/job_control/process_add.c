/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/14 02:37:44 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"
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
	p->argv = (char **)context->params->tbl;
	p->next = NULL;
	return (p);
}

int			process_add(t_context *context, pid_t pid)
{
	t_job		*j;		//	current job
	t_process	*p;		//	process iterator
	t_process	*new_p;	//	the newly created process

	// while(g_lock == JOB_ACCESS_LOCKED)
	// 	;
	// g_lock = JOB_ACCESS_LOCKED;

	ft_printf("Adding process %d, ", pid);
	ft_printf("and the context: ");
	print_tab((char **)context->params->tbl);
	// create the process with the pid pid
	if ((new_p = process_create(context, pid)) == NULL)
	{
		// g_lock = JOB_ACCESS_UNLOCKED;
		return (FAILURE);
	}
	// iterate to the last job created (current job)
	j = g_first_job;
	while (j->next != NULL)
		j = j->next;
	ft_printf("to the job number: %d\n", j->number);
	// if it's the first process in the current job, make it the process group leader
	if (j->empty_process == 1)
	{
		j->empty_process = 0;
		// ft_printf("making process: %d the group leader\n", pid);
		ft_printf("making the process leader: ");
		print_tab((char **)context->params->tbl);
		if ((setpgid(pid, pid)) < 0)
		{
			// g_lock = JOB_ACCESS_UNLOCKED;
			return (FAILURE);
		}
		j->pgid = pid;
		j->first_process = new_p;
		job_print();
		// g_lock = JOB_ACCESS_UNLOCKED;
		return (SUCCESS);
	}
	// if not, append it to the process list (to be the last process)
	p = j->first_process;
	while (p->next != NULL)
		p = p->next;
	if (p->pid == pid)
		return (SUCCESS);
	p->next = new_p;
	// make it part of the existing process group
	if ((setpgid(pid, j->pgid)) < 0)
		return (FAILURE);
	job_print();
	return (SUCCESS);
}