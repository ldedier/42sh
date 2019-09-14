/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:55:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/15 00:04:08 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "job_control.h"

int			job_exec(void)
{
	t_job	*j;

	j = g_job_control->first_job;
	while (j != NULL)
	{
		job_start(j, 1);
		j = j->next;
	}
	return (SUCCESS);	//	change this of course...
}