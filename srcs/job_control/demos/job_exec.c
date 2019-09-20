/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:55:06 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 15:51:04 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_21.h"
#include "sh_job_control.h"

int			job_exec(void)
{
	t_job	*j;

	j = g_job_ctrl->first_job;
	while (j != NULL)
	{
		job_start(j, 1);
		j = j->next;
	}
	return (SUCCESS);	//	change this of course...
}