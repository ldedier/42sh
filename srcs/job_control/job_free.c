/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 01:15:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/21 01:18:59 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

void			job_free(t_job *j)
{
	t_process	*p;
	t_process	*p_next;


	if (j == NULL)
		return ;
	p = j->first_process;
	while (p != NULL)
	{
		p_next = p->next;
		free(p);	//free_whole_process.
		p = p->next;
	}
	//free command.
	free(j);
}