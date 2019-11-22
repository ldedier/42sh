/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 00:38:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/21 11:07:03 by mdaoud           ###   ########.fr       */
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
	p->continued = 0;
	p->status = -1;
	p->next = NULL;
	return (p);
}

static int	create_process_cmd(t_job *j, t_process *p, int first_p)
{
	char	*str;

	ft_memset(p->cmd, MAX_PROCESS_LEN, '\0');
	if (first_p)
		str = ft_strtok_pipe(j->cmd_copy, "|");
	else
	{
		str = ft_strtok_pipe(NULL, "|");
		str = str + 1;
	}
	ft_strncpy(p->cmd, str, MAX_PROCESS_LEN);
	if (p->cmd[MAX_PROCESS_LEN - 2])
		ft_strcpy(p->cmd + MAX_PROCESS_LEN - 5, "[...]");
	return (SUCCESS);
}

int			process_add(pid_t pid)
{
	t_job		*j;
	t_process	*new_p;
	t_process	*p;

	if ((new_p = process_create(pid)) == NULL)
		return (sh_perror("Process add", SH_ERR1_MALLOC));
	j = g_job_ctrl->curr_job;
	if (j->first_process == NULL)
	{
		create_process_cmd(j, new_p, 1);
		j->first_process = new_p;
		return (SUCCESS);
	}
	create_process_cmd(j, new_p, 0);
	p = j->first_process;
	while (p->next != NULL)
		p = p->next;
	p->next = new_p;
	return (SUCCESS);
}
