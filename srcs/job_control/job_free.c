/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 01:52:35 by mdaoud            #+#    #+#             */
/*   Updated: 2019/10/08 18:40:23 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"

void		job_free(t_job *j)
{
	t_process	*p;
	t_process	*p_next;

	if (j == NULL)
		return ;
	free(j->command);
	j->command = NULL;
	p = j->first_process;
	while(p != NULL)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
	free(j);
}