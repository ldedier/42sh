/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 15:54:13 by mdaoud            #+#    #+#             */
/*   Updated: 2019/09/20 15:56:27 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_job_control.h"
#include "sh_21.h"

/*
** For each commandline input.
** Reset the jobs structure
** No frees are implemented yet
*/

int			jobs_reset(void)
{
	g_job_ctrl->job_count = 1;
	g_job_ctrl->curr_job = NULL;
	g_job_ctrl->first_job = NULL;
	return (SUCCESS);
}