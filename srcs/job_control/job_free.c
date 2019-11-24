/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:52:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/11/24 15:10:15 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"

void		job_free(t_job *j)
{
	t_process	*p;
	t_process	*p_next;

	if (j == NULL)
		return ;
	if (j->command)
		free(j->command);
	j->command = NULL;
	if (j->cmd_copy)
		free(j->cmd_copy);
	j->cmd_copy = NULL;
	p = j->first_process;
	while (p != NULL)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
	free(j);
}
