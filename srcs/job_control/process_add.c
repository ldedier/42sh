/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/15 04:38:19 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"
#include "libft.h"
#include "sh_grammar.h"

t_process	*process_create(pid_t pid)
{
	t_process	*p;

	if ((p = malloc(sizeof(t_process))) == NULL)
		return (NULL);
	p->pid = pid;
	p->completed = 0;
	p->stopped = 0;
	p->status = -1;
	p->next = NULL;
	return (p);
}

static int	create_process_cmd(t_job *j, t_process *p, int first_p)
{
	char	*str;

	ft_memset(p->cmd, MAX_PROCESS_LEN, '\0');
	if (first_p)
		str = ft_strtok(j->cmd_copy, "|");
	else
	{
		str = ft_strtok(NULL, "|");
		str = str + 1;
	}
	ft_strcpy(p->cmd, str);
	return (SUCCESS);
}

int			process_add(pid_t pid)
{
	t_job		*j;		//	current job
	t_process	*p;		//	process iterator
	t_process	*new_p;	//	the newly created process

	// create the process with the pid pid
	if ((new_p = process_create(pid)) == NULL)
		return (jobs_error_free(SH_ERR1_MALLOC, "process_add", 1, FAILURE));
	// Go to the last job
	j = g_job_ctrl->curr_job;
	// if it's the first process in the current job, make it the process group leader
	if (j->first_process == NULL)
	{
		create_process_cmd(j, new_p, 1);
		j->first_process = new_p;
		return (SUCCESS);
	}
	create_process_cmd(j, new_p, 0);
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
